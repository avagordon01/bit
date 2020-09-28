project('bit', 'cpp',
  default_options: [
    'buildtype=debugoptimized',
    'warning_level=3',
    'werror=true',
    'b_sanitize=address,undefined',
    'b_lundef=false',
  ]
)

gtest = subproject('gtest').get_variable('gtest_main_dep')

types = [
  #'uint8_t',
  #'uint16_t',
  #'uint32_t',
  'uint64_t',
]
cpp_versions = [
  #'c++11',
  #'c++14',
  'c++17',
]
foreach cpp_version : cpp_versions
  foreach type : types
    name = 'bit-test-' + cpp_version + '-' + type
    test(name, executable(name, 'bit-test.cc', dependencies: [gtest],
      override_options: ['cpp_std=' + cpp_version],
      cpp_args: ['-DTYPE=' + type],
    ))
  endforeach
endforeach
