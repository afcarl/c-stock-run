Import('env')

sources = env.Glob('src/*.c')

ret = []

lib_paths = ['${BUILD_ROOT}/third-party/sdl2/lib/x64/',
             '${BUILD_ROOT}/third-party/sdl2_image/lib/x64/',
             '${BUILD_ROOT}/third-party/sdl2_mixer/lib/x64/',
             '${BUILD_ROOT}/third-party/sdl2_ttf/lib/x64/',
             '${BUILD_ROOT}/third-party/glew/bin/Release/x64/',
             #'${BUILD_ROOT}/third-party/glew/lib/Release/x64/',
             ]

libs = [
    '${BUILD_ROOT}/third-party/glew/lib/Release/x64/glew32.lib',
    'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.17763.0/um/x64/OpenGL32.lib',
    'C:/Program Files (x86)/Windows Kits/10/Lib/10.0.17763.0/um/x64/GlU32.Lib',
    ]
installs = []

for p in lib_paths:
    libs.extend(env.Glob(p + '*.lib'))
    installs.append(env.Install('.',env.Glob(p + '*.dll')))

ret.append(installs)
ret.append(env.Program('c4',[libs,sources,]))
Return('ret')