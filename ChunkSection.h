#pragma once

#include "scottbase/Unknown.h"
#include "cppNBT\src\cppnbt.h"

class ChunkSection : public Unknown
{
public:
	ChunkSection(nbt::TagCompound *section);

	unsigned int		getSectionY() const;
	unsigned int		getBlockIdAt(unsigned int x, unsigned int y, unsigned int z) const;

	//unknown
    const char			*getClassName() const;

	void				dump() const;

protected:
	~ChunkSection();

	nbt::TagCompound *m_pSection;

};

