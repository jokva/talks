with segyio.open(source, ignore_geometry=True) as src:
    spec = segyio.tools.metadata(src)
    spec.samples = spec.samples[:int(src.samples.size/2)]
    with segyio.create(destination, spec) as dst:
        dst.text[0] = src.text[0]
        dst.bin = src.bin
        for ix, trace in enumerate(src.trace):
            dst.trace[ix] =  scipy.signal.resample(trace, int(len(trace)/2))
        dst.bin.update(hdt=new_sampling*1000)
        dst.bin.update(hns=len(spec.samples))
        dst.header = src.header

plot(destination)
