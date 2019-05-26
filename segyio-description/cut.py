with segyio.open(filename, ignore_geometry=True) as src:
    spec = segyio.tools.metadata(src)
    spec.samples = spec.samples[:depth]
    with segyio.create(destination, spec) as dst:
        dst.text[0] = src.text[0]
        dst.bin = src.bin
        dst.bin.update(hns=len(spec.samples))
        dst.header = src.header
        dst.trace = src.trace
