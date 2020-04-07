project('mail-it', 'cpp', 
        default_options: ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

cc = meson.get_compiler('cpp')

nana = cc.find_library('libnana', dirs: [get_option('nana_dir')])

thread_dep = dependency('threads')
x11_dep = dependency('x11')
xext_dep = dependency('xext')
xrandr_dep = dependency('xrandr')
glu_dep = dependency('glu')
gl_dep = dependency('gl')
xft_dep = dependency('xft')
fontconfig_dep = dependency('fontconfig')

inc_dir = include_directories(['include', 
                                get_option('nana_include_dir')])


src = ['src/main.cpp']

executable('mail-it', 
           sources : src,
           include_directories : [inc_dir],
           dependencies: [nana, thread_dep, fontconfig_dep, x11_dep, xext_dep, xft_dep, xrandr_dep, gl_dep, glu_dep]
           )