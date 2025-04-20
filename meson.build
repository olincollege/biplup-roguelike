# Change these to suit your project, if you want.
project(
  'dino-game', 'c',
  version: '0.40.0',
  license: 'Zlib',
  meson_version: '>=0.60.0',
  default_options: ['buildtype=debugoptimized', 'warning_level=2', 'c_std=c11', 'cpp_std=c++20'])

# Set up recommended compiler and linker flags.
subdir('meson/toolchain')

# If you're working on meson-gba
if get_option('dev')
  subdir('meson/dev')
  subdir_done()
endif

# The name of your project.
name = 'dino-game'

# All of the source files used by your project.
sources = [
  'src/move.c',
  'src/util.c',
  'src/score.c',
  'src/player_movement.c',
  'src/main.c',
  'src/blob.s',
  'src/bg_with_road.s'
]

player_movement_sources = [
    'src/blob.s',
    'src/player_movement.c',
    'src/player_movement_example.c'
]

collisions_sources = [
  'src/blob.s',
  'src/player_movement.c',
  'src/collisions_example.c',
  'src/move.c',
  'src/util.c'
]

score_sources = [
  'src/score.c',
  'src/score_example.c'
]

player_movement_with_score_sources = [
  'src/blob.s',
  'src/player_movement.c',
  'src/score.c',
  'src/player_movement_with_score_example.c'
]

# All of the include directories used by your project.
includes = [
  'include',
]

# Dependencies. gba-meson provides a large number of GBA development libraries.
# Check them out and add the ones you want to use to this list.
dependencies = [
  dependency('minrt'),
  dependency('libtonc')
]

# The main executable for your game. We give it a '.elf' file extension,
# just to make the file more easy to differentiate from a raw ROM.
elf = executable(
  name,
  sources,
  include_directories: includes,
  dependencies: dependencies,
  name_suffix: 'elf'
)

player_movement_elf = executable(
  'player_movement',
  player_movement_sources,
  include_directories: includes,
  dependencies: dependencies,
  name_suffix: 'elf'
)

collisions_elf = executable(
  'collisions',
  collisions_sources,
  include_directories: includes,
  dependencies: dependencies,
  name_suffix: 'elf'
)

score_elf = executable(
  'score',
  score_sources,
  include_directories: includes,
  dependencies: dependencies,
  name_suffix: 'elf'
)

player_score_elf = executable(
  'player_score',
  player_movement_with_score_sources,
  include_directories: includes,
  dependencies: dependencies,
  name_suffix: 'elf'
)

# Get the 'makerom' program from sdk-seven.
makerom = find_program('makerom')

# Build a raw GBA ROM file from your ELF file.
rom = custom_target(
  name + '-rom',
  input: elf,
  output: name + '.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true
)

player_movement_rom = custom_target(
    'player-movement-rom',
  input: player_movement_elf,
  output: 'player_movement.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true
)

collisions_rom = custom_target(
  'collisions-rom',
  input: collisions_elf,
  output: 'collisions.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true
)

score_rom = custom_target(
  'score-rom',
  input: score_elf,
  output: 'score.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true
)

player_score_rom = custom_target(
  'player-score-rom',
  input: player_score_elf,
  output: 'player_score.gba',
  command: [makerom, '@INPUT@', '@OUTPUT@'],
  build_by_default: true
)
