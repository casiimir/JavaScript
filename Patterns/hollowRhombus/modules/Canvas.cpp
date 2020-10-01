#include <iostream>
#include <string>
#include <cstring>

#include "../headers/Canvas.hpp"

using std::cout;
using std::strcat;
using std::string;

Canvas::Canvas(int canvasSize, Pixel pixelType)
{
	this->size = {canvasSize, canvasSize};
	this->block = pixelType;
	this->calcContentSize();
}

void Canvas::calcContentSize()
{
	int contentSize = this->size.width - 2;
	this->conSize = {contentSize, contentSize};
}

void Canvas::draw()
{
	string lines = this->generate();
	std::cout << lines << std::endl;
}

string Canvas::generate()
{
	string canvas = "\n";
	for (int y = 0; y < this->size.height; y++)
		for (int x = 0; x < this->size.width; x++)
		{
			bool isInContent = this->isInContent({x, y});
			canvas += isInContent ? this->addShape({x - 1, y - 1}) : this->addFrame({x, y});
		}
	return canvas;
}

bool Canvas::isInContent(PointerPosition p)
{
	bool top = p.y >= 1;
	bool left = p.x >= 1;
	bool right = p.x <= this->conSize.width;
	bool bottom = p.y <= this->conSize.height;
	return left && right && top && bottom;
}

string Canvas::addFrame(PointerPosition p)
{
	bool isTop = p.y == 0;
	bool isRight = p.x == 0;
	bool isBottom = p.y + 1 == this->size.height;
	bool isLeft = p.x + 1 == this->size.width;

	if (isTop && isLeft || isLeft)
		return this->addBlock(this->block.solid, '\n');
	else if (isTop || isRight || isBottom)
		return this->addBlock(this->block.solid);

	return "";
}

string Canvas::addShape(PointerPosition conPos)
{
	// TODO
	int increasingVerticalParam = conPos.y <= this->conSize.height / 2 ? conPos.y : this->conSize.height - 1 - conPos.y;
	int shapeSize = 1 + (increasingVerticalParam * 2);
	int emptySize = this->conSize.width - shapeSize;
	Area shapeArea{
		emptySize / 2 - 1, // -1 due to pos start from 0
		shapeSize + emptySize / 2,
	};
	if (conPos.x > shapeArea.start && conPos.x < shapeArea.end)
		return this->addBlock(this->block.hollow);
	return this->addBlock(this->block.solid);
}

string Canvas::addBlock(char block)
{
	return this->addBlock(block, ' ');
}

string Canvas::addBlock(char block, char padding)
{
	return string(1, block) + string(1, padding);
}