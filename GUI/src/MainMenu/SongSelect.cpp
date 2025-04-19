#include "SongSelect.h"
#include "../Util/VertexHelper.h"
#include "MainMenuGlobals.h"
#include <cmath>

#define TEMP_LISTINGS_COUNT 100

namespace o2 {

SongSelect::SongSelect(
	int listingHeight,
	float listingSpacing,
	float scrollBarWidth,
	sf::Vector2u size,
	sf::IntRect visibleWindow,
	sf::ContextSettings settings
) : gui::Div(size, visibleWindow, settings) 
{
	scrollable = true;
	clickEnabled = true;
	hoverable = true;
	this->sizef = sf::Vector2f(size);
	this->listingSpacing = listingSpacing;
	this->scrollBarWidth = scrollBarWidth;
	this->listingHeight = listingHeight;

	listingUpdateLimiter.setLimit(60);

	background.setFillColor(sf::Color(128, 128, 128));
	background.setSize(sizef);

	listingVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
	listingVertices.resize(maxListings * 12);

	listingTexts.resize(maxListings * 2);

	for (int i = 0; i < maxListings; i++) {
		//TEMP
		index.push_back(i);
	}
	updateListings();

	viewCenterPos = renderTexture.getView().getCenter();
	viewBounds.x = viewCenterPos.y;
	viewBounds.y = listingHeight * TEMP_LISTINGS_COUNT * (1.f + listingSpacing) - viewCenterPos.y;

	scrollButton = new gui::ScrollBarButton(
		{ sizef.x * scrollBarWidth, sizef.y * 0.05f },
		gui::ScrollSide::Vertical,
		{ sizef.x * scrollBarWidth, sizef.y - sizef.x * scrollBarWidth - sizef.y * 0.05f }
	);

	scrollEndButtonTop = new gui::ScrollEndButton(
		{ (unsigned int)(sizef.x * scrollBarWidth), (unsigned int)(sizef.x * scrollBarWidth) },
		gui::ScrollDirection::UP_RIGHT,
		scrollButton
	);
	scrollEndButtonTop->setPosition({ 
		sizef.x - sizef.x * scrollBarWidth, 
		scrollButton->getLowestPointOfBar() - sizef.x * scrollBarWidth 
	});

	scrollEndButtonBottom = new gui::ScrollEndButton(
		{ (unsigned int)(sizef.x * scrollBarWidth), (unsigned int)(sizef.x * scrollBarWidth) },
		gui::ScrollDirection::DOWN_LEFT,
		scrollButton
	);
	scrollEndButtonBottom->setPosition({
		sizef.x - sizef.x * scrollBarWidth,
		scrollButton->getHighestPointOfBar()
	});

	scrollButton->setPosition({ sizef.x - sizef.x * scrollBarWidth, sizef.x * scrollBarWidth });

	elements.push_back(&listingVertices);
	for (int i = 0; i < listingTexts.size(); i++) {
		elements.push_back(&listingTexts[i]);
	}
}

SongSelect::~SongSelect() {
	delete scrollButton;
	delete scrollEndButtonBottom;
	delete scrollEndButtonTop;
}

void SongSelect::click(sf::Vector2f mousePos, sf::Mouse::Button button) {
	if (scrollButton and scrollEndButtonBottom and scrollEndButtonTop) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		scrollButton->click(relativeMousePos, button);
		scrollEndButtonBottom->click(relativeMousePos, button);
		scrollEndButtonTop->click(relativeMousePos, button);
	}
}

void SongSelect::releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) {
	sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
	if (scrollButton and scrollEndButtonBottom and scrollEndButtonTop) {
		scrollButton->releaseClick(relativeMousePos, button);
		scrollEndButtonBottom->releaseClick(relativeMousePos, button);
		scrollEndButtonTop->releaseClick(relativeMousePos, button);
	}

	//relativeMousePos = renderTexture.getView().getInverseTransform().transformPoint(mousePos);
	for (int i = 0; i < index.size(); i++) {
		sf::Vector2f posWithView = { relativeMousePos.x, relativeMousePos.y + (viewCenterPos.y - viewBounds.x) };
		if (vh::containedByQuad(&listingVertices[i * 12], posWithView)) {
			printf("Clicked listing: %d\n", index[i]);
		}
	}
}

void SongSelect::handleHover(sf::Vector2f mousePos) {
	if (scrollButton and scrollEndButtonBottom and scrollEndButtonTop) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		scrollButton->handleHover(relativeMousePos);
		scrollEndButtonBottom->handleHover(relativeMousePos);
		scrollEndButtonTop->handleHover(relativeMousePos);
	}
}

void SongSelect::adjustFixedPositionElements(float delta) {
	background.move({ 0, delta }); // temp
	scrollButton->move({ 0, delta });
	scrollEndButtonBottom->move({ 0, delta });
	scrollEndButtonTop->move({ 0, delta });
}

void SongSelect::adjustScrollBarPosition() {
	if (scrollButton) {
		float percent = (viewCenterPos.y - viewBounds.x) / (viewBounds.y - viewBounds.x);
		float dragRange = scrollButton->dragMaxY - scrollButton->dragMinY;
		scrollButton->setPosition({ scrollButton->getPosition().x, scrollButton->dragMinY + percent * dragRange });
	}
}

void SongSelect::moveView(float delta) {
	viewCenterPos.y += delta;
	viewCenterPos.y = std::min(viewCenterPos.y, viewBounds.y);
	viewCenterPos.y = std::max(viewCenterPos.y, viewBounds.x);
	
	updateView();
	adjustScrollBarPosition();
}

void SongSelect::updateView() {
	sf::View view = renderTexture.getView();
	view.setCenter(viewCenterPos);
	renderTexture.setView(view);

	// i use a loop here to keep updating the listings until no longer needed
	// this is needed for when user scrolls fast
	while (true) {
		size_t leastIndex = getIndexOfLeastIndex();
		float lowY = listingVertices[leastIndex * 12].position.y;

		size_t greatestIndex = getIndexOfGreatestIndex();
		float highY = listingVertices[greatestIndex * 12 + 5].position.y;

		if (index[leastIndex] > 0 and viewCenterPos.y - lowY < 700) {
			index[greatestIndex] = index[leastIndex] - 1;
		}
		else if (index[greatestIndex] < TEMP_LISTINGS_COUNT and highY - viewCenterPos.y < 700) {
			index[leastIndex] = index[greatestIndex] + 1;
		}
		else {
			break;
		}
		updateListings();
	}
}

void SongSelect::setViewPosByPercent(float percent) {
	percent = std::max(0.f, percent);
	percent = std::min(1.f, percent);

	viewCenterPos.y = viewBounds.x + percent * (viewBounds.y - viewBounds.x);

	updateView();
	adjustScrollBarPosition();
}

void SongSelect::scroll(sf::Vector2f mousePos, float delta) {
	if (scrollable) {
		if (visiblyContains(mousePos)) {
			if (delta > 0) {
				moveView(10);
			}
			else {
				moveView(-10);
			}
		}
	}
}

void SongSelect::update() {
	gui::Div::update();

	scrollEndButtonBottom->update();
	scrollEndButtonTop->update();

	if (listingUpdateLimiter.isReady()) {
		if (scrollButton) {
			float percent = scrollButton->getScrollPercentage();
			setViewPosByPercent(percent);
		}
	}
}

size_t SongSelect::getIndexOfLeastIndex() const {
	int least = 0x0FFFFFFF; // arbitrary large number
	size_t leastIndex = 0;
	for (int i = 0; i < index.size(); i++) {
		if (index[i] < least) {
			least = index[i];
			leastIndex = i;
		}
	}
	return leastIndex;
}

size_t SongSelect::getIndexOfGreatestIndex() const {
	int greatest = -100; // arbitrary small number
	size_t greatestIndex = 0;
	for (int i = 0; i < index.size(); i++) {
		if (index[i] > greatest) {
			greatest = index[i];
			greatestIndex = i;
		}
	}
	return greatestIndex;
}

void SongSelect::updateListings() {
	for (int j = 0; j < index.size(); j++) {
		int i = index[j];

		sf::FloatRect listingBgBounds;
		listingBgBounds.size = sf::Vector2f({ sizef.x * (1.f - scrollBarWidth), (float)listingHeight });
		listingBgBounds.position = { 0, listingHeight * i * (1.f + listingSpacing) };

		sf::FloatRect listingMapBgBounds;
		listingMapBgBounds.size = sf::Vector2f({ listingBgBounds.size.x * 0.4f, (float)listingHeight });
		listingMapBgBounds.position = { listingBgBounds.size.x * 0.6f, listingHeight * i * (1.f + listingSpacing) };

		size_t offset = j * 12;
		vh::positionQuad(&listingVertices[offset], listingBgBounds);
		vh::colorQuad(&listingVertices[offset], sf::Color::Black);
		vh::positionQuad(&listingVertices[offset + 6], listingMapBgBounds);
		vh::colorQuad(&listingVertices[offset + 6], sf::Color::Blue);

		listingTexts[2 * j].setFont(minecraftFont);
		listingTexts[2 * j].setString("Top Text " + std::to_string(i));
		listingTexts[2 * j].setPosition({
			listingBgBounds.size.x * 0.05f + listingBgBounds.position.x,
			listingBgBounds.size.y / 3.f - listingTexts[2 * j].getBoundingBox().size.y / 2.f + listingBgBounds.position.y
			});
		listingTexts[2 * j + 1].setFont(minecraftFont);
		listingTexts[2 * j + 1].setString("Bottom Text");
		listingTexts[2 * j + 1].setPosition({
			listingBgBounds.size.x * 0.05f + listingBgBounds.position.x,
			2.f * listingBgBounds.size.y / 3.f - listingTexts[2 * j].getBoundingBox().size.y / 2.f + listingBgBounds.position.y
			});
	}
}

void SongSelect::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RenderStates statesCopy = states;

	states.transform *= getTransform();

	target.draw(background, states);
	target.draw(*scrollEndButtonBottom, states);
	target.draw(*scrollEndButtonTop, states);
	target.draw(*scrollButton, states);

	states = statesCopy;
	gui::Div::draw(target, states);
}

}