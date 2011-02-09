#! /usr/bin/env python
# encoding: utf-8

VERSION='0.0.1'
APPNAME='mpl_tree'

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')

def build(bld):
    bld.program(
        source = 'test.cpp',
        target = 'test_mpl_tree',
        cxxflags = ['-O2', '-Wall', '-std=c++0x'],
        includes = '.')

