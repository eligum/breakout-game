Lines beginning with '#'
	When reading the file for each level any line beginning with a '#' is
	interpreted as a comment, and therefore ingnored.
Each number represents a brick:
	0 => no brick, an empty space within the level
	1 => a solid brick, a brick that cannot be destroyed
	>1 => a destroyable brick, each number from 2 to 9 only differs in color