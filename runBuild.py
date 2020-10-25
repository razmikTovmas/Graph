#!/usr/bin/python3
import os
from os import path
from os import listdir

def createBuildDir():
    if not path.exists('./build'):
        os.makedirs('./build')
    return

def make():
    os.chdir('./build')
    os.system('cmake ..')
    os.system('make -j {0}'.format(os.cpu_count()))
    os.chdir('..')
    return

def getTestCases():
    cases = []
    for f in listdir('./examples'):
        cases.append(os.path.splitext(f)[0])
    return cases

def runTestCases():
    cases = getTestCases()
    os.chdir('./build/examples')
    for case in cases:
        os.system('./{0}'.format(case))
    return

def main():
    createBuildDir()
    make()
    runTestCases()
    return

if __name__ == "__main__":
    main()
