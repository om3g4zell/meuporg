#include "TileMap.hpp"

TileMap::TileMap(sf::Uint64 width, sf::Uint64 height)
    : m_vertices(sf::Quads, width * height * 4)
    , m_width(width)
    , m_height(height)
{
    for(sf::Uint64 i(0) ; i < m_height ; ++i)
    {
        std::vector<sf::Uint64> m_row;
        for(sf::Uint64 j(0) ; j < m_width ; ++j)
        {
            sf::Vertex* tile = &m_vertices[(i * m_width + j) * 4];
            tile[0].position = sf::Vector2f(32 * j, 32 * i);
            tile[1].position = sf::Vector2f(32 * (j + 1), 32 * i);
            tile[2].position = sf::Vector2f(32 * (j + 1), 32 * (i + 1));
            tile[3].position = sf::Vector2f(32 * j, 32 * (i + 1));

            m_row.push_back(0);
        }
        m_tileData.push_back(m_row);
    }
}

TileMap::~TileMap()
{

}

void TileMap::setTexturePtr(sf::Texture* ptr)
{
    m_texturePtr = ptr;
}

void TileMap::addTextureRect(sf::Uint64 code, sf::IntRect textureRect)
{
    m_textureRectCode[code] = textureRect;
}

void TileMap::setTileData(std::vector<std::vector<sf::Uint64>> tileData)
{
    m_tileData = tileData;
}

void TileMap::setTileData(sf::Vector2u index, sf::Uint64 value)
{
    m_tileData[index.x][index.y] = value;
}

void TileMap::update()
{
    for(sf::Uint64 i(0) ; i < m_height ; ++i)
    {
        for(sf::Uint64 j(0) ; j < m_width ; ++j)
        {
            sf::IntRect textureRect = m_textureRectCode[m_tileData[i][j]];
            sf::Vertex* tile = &m_vertices[(i * m_width + j) * 4];

            tile[0].texCoords = sf::Vector2f(textureRect.left, textureRect.top);
            tile[1].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top);
            tile[2].texCoords = sf::Vector2f(textureRect.left + textureRect.width, textureRect.top + textureRect.height);
            tile[3].texCoords = sf::Vector2f(textureRect.left, textureRect.top + textureRect.height);
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = m_texturePtr;

    target.draw(m_vertices, states);
}
