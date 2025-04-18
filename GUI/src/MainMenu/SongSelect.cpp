#include "SongSelect.h"
#include "../Util/VertexHelper.h"
#include "MainMenuGlobals.h"
#include <cmath>

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

	listingUpdateLimiter.setLimit(60);

	sf::Vector2f sizef = sf::Vector2f(size);
	background.setFillColor(sf::Color(128, 128, 128));
	background.setSize(sizef);

	listingVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
	listingVertices.resize(maxListings * 12);

	listingTexts.resize(maxListings * 2);

	for (int i = 0; i < maxListings; i++) {
		//TEMP
		index.push_back(i);

		sf::FloatRect listingBgBounds;
		listingBgBounds.size = sf::Vector2f({ sizef.x * (1.f - scrollBarWidth), (float)listingHeight });
		listingBgBounds.position = { 0, listingHeight * i * (1.f + listingSpacing) };

		sf::FloatRect listingMapBgBounds;
		listingMapBgBounds.size = sf::Vector2f({ listingBgBounds.size.x * 0.4f, (float)listingHeight });
		listingMapBgBounds.position = { listingBgBounds.size.x * 0.6f, listingHeight * i * (1.f + listingSpacing) };

		size_t offset = i * 12;
		vh::positionQuad(&listingVertices[offset], listingBgBounds);
		vh::colorQuad(&listingVertices[offset], sf::Color::Black);
		vh::positionQuad(&listingVertices[offset + 6], listingMapBgBounds);
		vh::colorQuad(&listingVertices[offset + 6], sf::Color::Blue);

		listingTexts[2 * i].setFont(minecraftFont);
		listingTexts[2 * i].setString("Top Text");
		listingTexts[2 * i].setPosition({
			listingBgBounds.size.x * 0.05f + listingBgBounds.position.x,
			listingBgBounds.size.y / 3.f - listingTexts[2 * i].getBoundingBox().size.y / 2.f + listingBgBounds.position.y
		});
		listingTexts[2 * i + 1].setFont(minecraftFont);
		listingTexts[2 * i + 1].setString("Bottom Text");
		listingTexts[2 * i + 1].setPosition({
			listingBgBounds.size.x * 0.05f + listingBgBounds.position.x,
			2.f * listingBgBounds.size.y / 3.f - listingTexts[2 * i].getBoundingBox().size.y / 2.f + listingBgBounds.position.y
		});
	}

	viewCenterPos = renderTexture.getView().getCenter();
	viewBounds.x = viewCenterPos.y;
	viewBounds.y = listingHeight * maxListings * (1.f + listingSpacing) - viewCenterPos.y;

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

	//elements.push_back(&background);
	elements.push_back(&listingVertices);
	for (int i = 0; i < listingTexts.size(); i++) {
		elements.push_back(&listingTexts[i]);
	}
	//elements.push_back(scrollEndButtonTop);
	//elements.push_back(scrollEndButtonBottom);
	//elements.push_back(scrollButton);
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
	if (scrollButton and scrollEndButtonBottom and scrollEndButtonTop) {
		sf::Vector2f relativeMousePos = getInverseTransform().transformPoint(mousePos);
		scrollButton->releaseClick(relativeMousePos, button);
		scrollEndButtonBottom->releaseClick(relativeMousePos, button);
		scrollEndButtonTop->releaseClick(relativeMousePos, button);
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
	viewCenterPos.y = std::max(viewCenterPos.y, viewBounds.x);
	viewCenterPos.y = std::min(viewCenterPos.y, viewBounds.y);
	
	sf::View view = renderTexture.getView();
	view.setCenter(viewCenterPos);
	renderTexture.setView(view);
	adjustScrollBarPosition();
}

void SongSelect::setViewPosByPercent(float percent) {
	//sf::View view = renderTexture.getView();
	//float oldY = view.getCenter().y;
	//float newY = percent * (viewBounds.y - viewBounds.x) + viewBounds.x;
	//if (newY != oldY) {
	//	view.setCenter({ view.getCenter().x, newY });
	//	adjustFixedPositionElements(newY - oldY);
	//	renderTexture.setView(view);
	//}

	percent = std::max(0.f, percent);
	percent = std::min(1.f, percent);

	viewCenterPos.y = viewBounds.x + percent * (viewBounds.y - viewBounds.x);

	sf::View view = renderTexture.getView();
	view.setCenter(viewCenterPos);
	renderTexture.setView(view);
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