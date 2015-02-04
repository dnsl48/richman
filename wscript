#!/usr/sbin/env python


top = '.'
out = 'build'

APPNAME = 'richman'
VERSION = '0.7'


import os.path
import threading
import subprocess
import waflib
import waflib.Tools.cxx
import waflib.Tools.waf_unit_test


def configure (conf):
	conf.load ('compiler_cxx')
	conf.load ('waf_unit_test')

	conf.env.CXXFLAGS += ['-std=c++11', '-Wall']



def options (opt):
	opt.load ('compiler_cxx')
	opt.load ('waf_unit_test')

	opt.add_option ('--cldoc', action='store', help="Path to the cldoc generator")
	opt.add_option ('--debug', action='store_true', help='Building a debug version, with debugging flags')
	opt.add_option ('--gcovr', action='store_true', help='Building a version with code-coverage flags')
	opt.add_option ('--gprof', action='store_true', help='Building a version with a profiling data')
	opt.add_option ('--tests', action='store_true', help='Building an application and run the tests afterwards')


def build (ctx):
	withoutOptimization = False

	if ctx.options.cldoc:
		if ctx.options.cldoc == '-':
			ctx.options.cldoc = '~/.local/bin/cldoc'

		ctx.env.CLDOC_PATH = os.path.abspath (os.path.expanduser (ctx.options.cldoc))
		ctx.env.CLDOC_ARGS = ['--', '--basedir=' + ctx.path.abspath (), '--output=' + os.path.join (ctx.path.abspath (), out, 'cldocs')]
		ctx.env.CLDOC_SRCS = [i.abspath () for i in ctx.path.ant_glob ('**/*.hpp')] + [i.abspath () for i in ctx.path.ant_glob ('**/*.cpp')]

	if ctx.options.gcovr:
		ctx.env.CXXFLAGS += ['-fprofile-arcs', '-ftest-coverage']
		ctx.env.LINKFLAGS += ['-fprofile-arcs']
		ctx.env.LIB += ['gcov']
		withoutOptimization = True

	if ctx.options.gprof:
		ctx.env.CXXFLAGS += ['-pg']
		ctx.env.LINKFLAGS += ['-pg']
		withoutOptimization = True

	if ctx.options.debug:
		ctx.env.CXXFLAGS += ['-g']
		withoutOptimization = True

	if withoutOptimization:
		ctx.env.CXXFLAGS += ['-O0']

	if ctx.options.tests:
		ctx.options.all_tests = True
		ctx.options.testcmd = 'valgrind --error-exitcode=1 --leak-check-heuristics=all --errors-for-leak-kinds=definite,indirect,possible,reachable %s'
		ctx.add_post_fun(waflib.Tools.waf_unit_test.summary)

	testKoverage (ctx)

def testKoverage (ctx):
	'Builds tests'
	ctx.stlib (
		target = 'koverager',
		source = [
			'Koverager/Suite.cpp',
			'Koverager/Plan.cpp'
		],
		includes = '.'
	)

	ctx.stlib (
		target = 'confee',
		source = [
			'Richman/Confee/Frame.cpp',
			'Richman/Confee/Node.cpp',
			'Richman/Confee/Subject.cpp'
		],
		includes = '.'
	)

	ctx.stlib (
		target = 'testkoverage_richman_cases',
		includes = '.',
		use = 'koverager confee',
		source = [
			'TestKoverage/Richman/Confee/FrameBaseCase.cpp',
			'TestKoverage/Richman/Confee/NodeBaseCase.cpp',
			'TestKoverage/Richman/Confee/RboolBaseCase.cpp',
			'TestKoverage/Richman/Confee/RboxBaseCase.cpp',
			'TestKoverage/Richman/Confee/RdictBaseCase.cpp',
			'TestKoverage/Richman/Confee/RlistBaseCase.cpp',
			'TestKoverage/Richman/Confee/RnumberBaseCase.cpp',
			'TestKoverage/Richman/Confee/RstringBaseCase.cpp',
			'TestKoverage/Richman/Confee/SubjectBaseCase.cpp',
			'TestKoverage/Richman/Confee/VboolBaseCase.cpp',
			'TestKoverage/Richman/Confee/VboxBaseCase.cpp',
			'TestKoverage/Richman/Confee/VdictBaseCase.cpp',
			'TestKoverage/Richman/Confee/VlistBaseCase.cpp',
			'TestKoverage/Richman/Confee/VnumberBaseCase.cpp',
			'TestKoverage/Richman/Confee/VstringBaseCase.cpp',
			'TestKoverage/Richman/Exception/RichExceptionBaseCase.cpp',
			'TestKoverage/Richman/Text/StringBaseCase.cpp',
			'TestKoverage/Richman/Text/Scanner/BraceBaseCase.cpp',
			'TestKoverage/Richman/Text/Scanner/EscapeBaseCase.cpp',
			'TestKoverage/Richman/Text/Scanner/ParserBraceCase.cpp',
			'TestKoverage/Richman/Text/Scanner/ParserLongEscapeCase.cpp',
			'TestKoverage/Richman/Text/Scanner/ParserShortEscapeCase.cpp',
			'TestKoverage/Richman/Text/Scanner/ParserStopCase.cpp',
			'TestKoverage/Richman/Text/Scanner/StopBaseCase.cpp',
			'TestKoverage/Richman/Text/Scanner/StringResourceBaseCase.cpp',
			'TestKoverage/Richman/Text/Scanner/SymbolBaseCase.cpp'
		]
	)

	ctx.program (
		target = 'testkoverage_richman_plan',
		source = 'TestKoverage/Richman/main.cpp',
		includes = '.',
		use = 'testkoverage_richman_cases',
		features = ['gcovr', 'gprof', 'test', 'cldoc']
	)



@waflib.TaskGen.feature ('cldoc')
def runCldoc (self, **args):
	'cldoc tasks generator'
	if isinstance (self, waflib.TaskGen.task_gen) and hasattr (self.bld.options, 'cldoc'):
		if self.bld.options.cldoc:
			self.create_task ('Cldoc', self.source)


class Cldoc (waflib.Task.Task):
	'cldoc task'
	run_str = '${CLDOC_PATH} generate ${ARCH_ST:ARCH} ${CXXFLAGS} ${CPPFLAGS} ${FRAMEWORKPATH_ST:FRAMEWORKPATH} ${CPPPATH_ST:INCPATHS} ${DEFINES_ST:DEFINES} ${CLDOC_ARGS} ${CLDOC_SRCS}'
	scan = None


@waflib.TaskGen.feature ('gcovr')
def runGcovr (self, **args):
	'Gcovr tasks generator'
	if isinstance (self, waflib.TaskGen.task_gen) and 'gcov' in self.env.LIB:
		if self.bld.options.gcovr:
			self.create_task ('Gcovr', self.bld.path.find_resource (self.target))


class Gcovr (waflib.Task.Task):
	'Gcovr task'
	def run (self):
		base_gcovr = [
			'python2',
			"$(whereis gcovr | sed -e 's/gcovr: //g')",
			'-r',
			os.path.abspath ('.'),
			'-e', '^TestKoverage',
			'-e', '^Koverager',
			'--exclude-unreachable-branches'
		]

		caller (self.inputs[0].abspath ())
		caller (['mkdir', '-p', self.inputs[0].parent.abspath () + '/gcovr_report'])
		caller (' '.join (base_gcovr + ['--html', '--html-details', '-o', self.inputs[0].parent.abspath () + '/gcovr_report/report.html']), shell=True)
		caller (' '.join (base_gcovr + ['-o', self.inputs[0].parent.abspath () + '/gcovr_report/report.txt']), shell=True)
		caller (' '.join (base_gcovr + ['-b', '-o', self.inputs[0].parent.abspath () + '/gcovr_report/report-branch.txt']), shell=True)
		caller (' '.join (base_gcovr + ['--xml', '--xml-pretty', '-o', self.inputs[0].parent.abspath () + '/gcovr_report/report.xml']), shell=True)



@waflib.TaskGen.feature ('gprof')
def runGprof (self, **args):
	'Gprof tasks generator'
	if isinstance (self, waflib.TaskGen.task_gen) and '-pg' in self.env.LINKFLAGS:
		if self.bld.options.gprof:
			self.create_task ('Gprof', self.bld.path.find_resource (self.target))


class Gprof (waflib.Task.Task):
	'Gprof task'
	def run (self):
		caller (self.inputs[0].abspath ())

		caller ([
			'mv',
			self.inputs[0].parent.parent.abspath () + '/gmon.out',
			self.inputs[0].parent.parent.abspath () + '/' + out + '/gprof_report/gmon.out'
		])

		caller (['mkdir', '-p', self.inputs[0].parent.abspath () + '/gprof_report'])

		caller (
			['gprof', self.inputs[0].abspath (), self.inputs[0].parent.abspath () + '/gprof_report/gmon.out'],
			stdout = open (self.inputs[0].parent.abspath () + '/gprof_report/flat.txt', 'w')
		)



caller_cache = []
caller_semaphore = threading.Semaphore()

def caller (somewhat, **flags):
	'Just calls somewhat synchronously'
	caller_semaphore.acquire ()

	if not somewhat in caller_cache:
		subprocess.call (somewhat, **flags)
		caller_cache.append (somewhat)

	caller_semaphore.release ()



# Hint for GCOV absolute source paths generation
# Difference between our cxx and waflib.Tools.cxx.cxx is ${SRC[0].abspath}
@waflib.TaskGen.extension ('.cpp')
def cxx_hook (self,node):
	return self.create_compiled_task ('cxx', node)

class cxx (waflib.Tools.cxx.cxx):
	run_str = '${CXX} ${ARCH_ST:ARCH} ${CXXFLAGS} ${CPPFLAGS} ${FRAMEWORKPATH_ST:FRAMEWORKPATH} ${CPPPATH_ST:INCPATHS} ${DEFINES_ST:DEFINES} ${CXX_SRC_F}${SRC[0].abspath()} ${CXX_TGT_F}${TGT}'
	scan = None
