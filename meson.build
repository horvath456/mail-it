project('mail-it', 'cpp', 
        default_options: ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

cc = meson.get_compiler('cpp')

nana = cc.find_library('libnana', dirs: [get_option('nana_dir')])
SQLiteCpp = cc.find_library('libSQLiteCpp', dirs: [get_option('sqlitecpp_dir')])
mailclient = cc.find_library('libmailclient', dirs: [get_option('mailclient_dir')])

thread_dep = dependency('threads')
x11_dep = dependency('x11')
xext_dep = dependency('xext')
xrandr_dep = dependency('xrandr')
glu_dep = dependency('glu')
gl_dep = dependency('gl')
xft_dep = dependency('xft')
fontconfig_dep = dependency('fontconfig')
sqlite3_dep = dependency('sqlite3')
libcurl_dep = dependency('libcurl')

inc_dirs = include_directories(['include', 
                                get_option('nana_include_dir'),
                                get_option('sqlitecpp_include_dir'),
                                get_option('csv_include_dir'),
                                get_option('mailclient_include_dir'),
                                get_option('json_include_dir'),
                                get_option('inja_include_dir')])


src = ['src/main.cpp']

executable('mail-it', 
           sources : src,
           include_directories : [inc_dirs],
           dependencies: [nana, SQLiteCpp, mailclient, libcurl_dep, sqlite3_dep, thread_dep, fontconfig_dep, x11_dep, xext_dep, xft_dep, xrandr_dep, gl_dep, glu_dep]
           )