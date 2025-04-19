#include <SFML/Graphics.hpp>
#include "../GUI/Div.h"
#include "../GUI/Text.h"
#include "../GUI/SubElements/ScrollBarButton.h"
#include "../GUI/SubElements/ScrollEndButton.h"
#include "../Util/RateLimiter.h"
#include <deque>

namespace o2 {

class SongSelect : public gui::Div {
protected:
	// TEMP, this will be moved out of this div for tranform purposes
	// for now just shows div area visually
	sf::RectangleShape background;

	sf::RenderTexture mapBackgrounds;
	sf::VertexArray listingVertices;
	std::vector<gui::Text> listingTexts;
	std::vector<int> index;
	const size_t maxListings = 20;
	gui::ScrollBarButton* scrollButton;
	gui::ScrollEndButton* scrollEndButtonTop;
	gui::ScrollEndButton* scrollEndButtonBottom;
	sf::Vector2f viewBounds;
	sf::Vector2f viewCenterPos;

	sf::Vector2f sizef;
	float listingSpacing;
	float scrollBarWidth;
	int listingHeight;

	RateLimiter listingUpdateLimiter;

public:
	SongSelect(
		int listingHeight,
		float listingSpacing,
		float scrollBarWidth,
		sf::Vector2u size, 
		sf::IntRect visibleWindow = { {}, {} }, 
		sf::ContextSettings settings = {}
	);
	~SongSelect();

	virtual void click(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void releaseClick(sf::Vector2f mousePos, sf::Mouse::Button button) override;
	virtual void handleHover(sf::Vector2f mousePos) override;
	virtual void scroll(sf::Vector2f mousePos, float delta) override;
	virtual void update() override;

protected:
	void adjustFixedPositionElements(float delta);
	void adjustScrollBarPosition();
	void moveView(float delta);
	void updateView();
	void setViewPosByPercent(float percent);

	size_t getIndexOfLeastIndex() const;
	size_t getIndexOfGreatestIndex() const;
	void updateListings();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}