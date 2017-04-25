#pragma once

#include <map>

static std::map<std::string, std::map<std::string, std::string> > configInfo = {
	{ "L1InstSize:",{
		{ "type", "Size" },
		{ "flag", "-l1-isize" },
		{ "naming", "_1is" },
		{ "level", "Instruction"}
	}
	},
	{ "L1InstBlockSize:",{
		{ "type", "BlockSize" },
		{ "flag", "-l1-ibsize" },
		{ "naming", "_1ib" },
		{ "level", "Instruction" }

	}
	},
	{ "L1InstSubBlockSize:",{
		{ "type", "SubBlock Size" },
		{ "flag", "-l1-isbsize" },
		{ "naming", "_1isb" },
		{ "level", "Instruction" }
	}
	},
	{ "L1InstAssoc:",{
		{ "type", "Associtivity" },
		{ "flag", "-l1-iassoc" },
		{ "naming", "_1ia" },
		{ "level", "Instruction" }
	}
	},
	{ "L1DataSize:",{
		{ "type", "Size" },
		{ "flag", "-l1-dsize" },
		{ "naming", "_1ds" },
		{ "level", "Data" }
	}
	},
	{ "L1DataBlockSize:",{
		{ "type", "BlockSize" },
		{ "flag", "-l1-dbsize" },
		{ "naming", "_1db" },
		{ "level", "Data" }
	}
	},
	{ "L1DataSubBlockSize:",{
		{ "type", "SubBlock Size" },
		{ "flag", "-l1-dsbsize" },
		{ "naming", "_1dsb" },
		{ "level", "Data" }
	}
	},
	{ "L1DataAssoc:",{
		{ "type", "Associtivity" },
		{ "flag", "-l1-dassoc" },
		{ "naming", "_1da" },
		{ "level", "Data" }
	}
	},
	{ "L2Size:",{
		{ "type", "Size" },
		{ "flag", "-l2-usize" },
		{ "naming", "_2s" },
		{ "level", "Level 2" }
	}
	},
	{ "L2BlockSize:",{
		{ "type", "BlockSize" },
		{ "flag", "-l2-ubsize" },
		{ "naming", "_2b" },
		{ "level", "Level 2" }
	}
	},
	{ "L2SubBlockSize:",{
		{ "type", "SubBlock Size" },
		{ "flag", "-l2-usbsize" },
		{ "naming", "_2sb" },
		{ "level", "Level 2" }
	}
	},
	{ "L2Assoc:",{
		{ "type", "Associtivity" },
		{ "flag", "-l2-uassoc" },
		{ "naming", "_2a" },
		{ "level", "Level 2" }
	}
	},
	{ "L2AssocHit:",{
		{ "type", "Hit" },
		{ "flag", "" },
		{ "naming", "_2ah" },
		{ "level", "Level 2" }
	}
	},
	{ "L2AssocMiss:",{
		{ "type", "Miss" },
		{ "flag", "" },
		{ "naming", "_2am" },
		{ "level", "Level 2" }
	}
	},
	{ "L3Size:",{
		{ "type", "Size" },
		{ "flag", "-l3-usize" },
		{ "naming", "_3s" },
		{ "level", "Level 3" }
	}
	},
	{ "L3BlockSize:",{
		{ "type", "BlockSize" },
		{ "flag", "-l3-ubsize" },
		{ "naming", "_3b" },
		{ "level", "Level 3" }
	}
	},
	{ "L3SubBlockSize:",{
		{ "type", "SubBlock Size" },
		{ "flag", "-l3-usbsize" },
		{ "naming", "_3sb" },
		{ "level", "Level 3" }
	}
	},
	{ "L3Assoc:",{
		{ "type", "Associtivity" },
		{ "flag", "-l3-uassoc" },
		{ "naming", "_3a" },
		{ "level", "Level 3" }
	}
	},
	{ "L3AssocHit:",{
		{ "type", "Hit" },
		{ "flag", "" },
		{ "naming", "_3ah" },
		{ "level", "Level 3" }
	}
	},
	{ "L3AssocMiss:",{
		{ "type", "Miss" },
		{ "flag", "" },
		{ "naming", "_3am" },
		{ "level", "Level 3" }
	}
	}
};