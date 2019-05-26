f = segyio.open(fname)
il, xl, t = f.ilines, f.xlines, f.samples
dt = t[1] - t[0]

# eagerly read into a 3D numpy ndarray
d = segyio.cube(f)
nil, nxl, nt = d.shape

plt.figure(figsize=(7, 9))
plt.imshow(
    d[nil//2].T,
    cmap='RdYlBu',
    vmin=-5,
    vmax=5,
    extent=(xl[0], xl[-1], t[-1], t[0])
)
plt.title('Seismic data')
plt.colorbar()
plt.axis('tight')
