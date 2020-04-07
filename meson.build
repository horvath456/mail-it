project('mail-it', 'cpp', 
        default_options: ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

cc = meson.get_compiler('cpp')

nana = cc.find_library('libnana', dirs: [get_option('nana_dir')])

inc_dir = include_directories(['include', 
                                get_option('nana_include_dir')])


src = ['src/main.cpp']

executable('mail-it', 
           sources : src,
           include_directories : [inc_dir],
           dependencies: nana,
           )