>>> f = segyio.open('f3.sgy')
>>> f.iline[273]
array([[ 1423.,  1953.,  2838., ..., -2119., -1238.,   304.],
       [ 1416.,  1718.,  3008., ..., -1630., -1444.,   -92.],
       [ 1290.,  1563.,  2549., ...,   -23., -1045.,  -788.],
       ...,
       [-1967.,  -984.,  1498., ...,  1767., -3605., -5437.],
       [-1678., -1571.,   261., ...,  3308., -1905., -5554.],
       [-1207., -2215.,  -361., ...,  4258.,  -215., -4885.]],
      dtype=float32)
>>> f.iline[273].shape
(201, 51)
>>> f.endian
'big'