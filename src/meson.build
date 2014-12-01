# Project file for blink lights.
project('blink-lights', 'cpp')
add_global_arguments('-std=gnu++14', language : 'cpp')
add_global_arguments('-funsigned-char', language : 'cpp')
add_global_arguments('-fdiagnostics-color=always', language : 'cpp')

fftw = dependency('fftw3')
openal = dependency('openal')
qt5 = dependency('qt5',
    modules : ['Widgets', 'PrintSupport'])

srcs = ['main.cpp', 'audio_plot.cpp', 'fourier_transform.cpp', 'qcustomplot.cpp', 'openal_capture.cpp']
executable('blink-lights',
    moc_headers : ['audio_plot.hpp', 'qcustomplot.h'],
    sources : srcs,
    dependencies : [fftw, openal, qt5]) 

# vim:et:sw=4:ts=4:tw=0:syntax=python:
