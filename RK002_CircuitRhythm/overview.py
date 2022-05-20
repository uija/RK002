mapping = (
	(0,'NOT USE'),
	(8, 'Sample'),
	(21, 'Pitch'),
	(17, 'Slices'),
	(16, 'Slice#'),
	(24, 'Slope'),
	(25, 'Distr'),
	(26, 'HPF'),
	(27, 'LPF'),
	(29, 'Level'),
	(30, 'Pan'),
	(31, 'Reverb'),
	(32, 'Delay')
)
for t in range( 1, 9):
	print( '| %d' % (t), end='')
	if t < 8:
		print( '\t\t', end='')
	else:
		print('|')
print()
for cc in range( 1, 13):
	s = ""
	for t in range( 0,8):
		s = s + '| %02d %s \t' % ( (t*12+cc), mapping[cc][1])
	print(s + '|')
