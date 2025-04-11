blob_image = files('blob.bmp')

grit = find_program('grit')

blob_data = custom_target('blob_sprite',
    input: blob_image,
    output: ['blob.s', 'blob.h'],
    command: [
        grit, '@INPUT@', '-gB4', '-gt', '-p', '-Mw 2', '-Mh 2', '-o', '@OUTDIR@/blob.s', '-W', '@OUTDIR@/blob.h'
    ],
    capture: false
)

blob_src = [blob_data]