# Sprite file name
object_name = 'blob'

blob_image = files(object_name + '.bmp')

grit = find_program('grit')

blob_data = custom_target(object_name + '_sprite',
    input: blob_image,
    output: [object_name + '.s', object_name + '.h'],
    command: [
        grit, '@INPUT@',
        '-gB4', '-gt', '-p', '-Mw 2', '-Mh 2', # Sprite options
        '-o', '@OUTDIR@/' + object_name + '.s',
        '-W', '@OUTDIR@/' + object_name + '.h'
    ],
    capture: false
)

blob_src = [blob_data]