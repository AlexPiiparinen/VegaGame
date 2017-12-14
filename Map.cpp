#include "Map.hpp"

CMap::CMap() : m_uMapHeight(0), m_uMapWidth(0), m_pszMap(NULL) {
	m_szTailset = "";
}

CMap::CMap(const char* szMapName) {
	std::ifstream fMap(szMapName, std::ios::in);
	if(!fMap) std::cerr << "[ERR]:\tCan't find level: \'" << szMapName << "\'!\n";
	
	char tmp[6];
	fMap.getline(tmp, 6);
	std::sscanf(tmp, "%d %d", &m_uMapHeight, &m_uMapWidth);
	if(!m_uMapHeight || !m_uMapWidth) std::cerr << "[ERR]:\tInvalid level!";
	
	m_pszMap = new std::string[m_uMapHeight];
	for(unsigned i=0; i<m_uMapHeight; i++) std::getline(fMap, m_pszMap[i]);
	
	std::getline(fMap, m_szTailset);
	m_Texture.loadFromFile("./Data/"+m_szTailset+".png");
	m_Sprite.setTexture(m_Texture);
	
	fMap.close();
}

CMap::~CMap() {
	m_uMapHeight = 0;
	m_uMapWidth = 0;
	m_szTailset = "";
	
	delete[] m_pszMap;
	m_pszMap = NULL;
}

void CMap::Render(sf::RenderWindow& wnd) {
	for(unsigned i=0; i<m_uMapHeight; i++)
		for(unsigned j=0; j<m_uMapWidth; j++) {
			if(m_pszMap[i][j] == '0') m_Sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
			if(m_pszMap[i][j] == '1') m_Sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			if(m_pszMap[i][j] == '2') m_Sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			
			m_Sprite.setPosition(j*32, i*32);
			wnd.draw(m_Sprite);
		}
}