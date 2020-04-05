project('mail-it', 'cpp', 
        default_options: ['cpp_std=c++2a', 'warning_level=3', 'werror=true'])

inc_dir = include_directories('include')

cc = meson.get_compiler('cpp')

src = ['src/main.cpp']

executable('mail-it', 
           sources : src,
           include_directories : [inc_dir],
           )