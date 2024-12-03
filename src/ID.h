#pragma once
namespace Textures {
	enum ID {
		Background, 
		Character1, 
		Block,
		Movement,
	};
}

namespace Fonts {
	enum ID {
		PixeloidMono,
		PixeloidSans,
		PixeloidSansBold,
	};
}
namespace States {
	enum ID {
		None,
		Menu, 
		Game, 
		Pause
	};
}
namespace Category {
	enum Type {
		None = 0, 
		Scene = 1 << 0, 
		Player = 1 << 1, 
		Enemy = 1 << 2, 
		Block = 1 << 3,
	};
}