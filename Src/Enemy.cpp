//����� ���������� ������� 21317�� 
// ����� �����

/*
	++	CEnemy (*)
	++	void checkCollisionWithMap(*)
	+-	void update(*)

	bool  m_bLife;
	int   m_nW, m_nH, m_nHealth;
	float m_fX, m_fY, m_fDx, m_fDy;
	float m_fSpeed, m_fCurrFrame;
	sf::Sprite  m_Sprite;
	fTime

*/

#include "Enemy.hpp"

using namespace sf;

CEnemy::CEnemy() : CEntity() {}

CEnemy::CEnemy(sf::Texture& Texture, float fX, float fY, int nW, int nH, std::string szName) : CEntity(Texture, fX, fY, nW, nH, szName) 
	{
		if (szName == "Army")
			{ //������ ������� ���� ������������� ��� ������ ������ ������. IntRect � ��� ���������� ����� 
				m_nW = nW; m_nH = nH;
				m_Sprite.setTextureRect(IntRect(0, 0, m_nW, m_nH));

				direction = rand() % (3); //����������� �������� ����� ����� ��������� ������� ����� ��������� ��������� ����� 
				m_fSpeed = 0.1f;//���� ��������.���� ������ ������ ��������� 
				m_fDx = m_fSpeed; 

				m_fX = fX; m_fY = fY;
			} 
	}

//�-��� �������� ������������ � ������
void  CEnemy::checkCollisionWithMap(float fDx, float fDy) { 
	/*		for (int i = m_fY / 32; i < (m_fY + m_nH) / 32; i++)//���������� �� ��������� ����� 
				for (int j = m_fX / 32; j < (m_fX + m_nW) / 32; j++) 
				{ 
					if (m_pszMapCode[i][j] == '0')//���� ������� - ������ �����
					{ 

					if (m_fDy > 0) 
					{ m_fY = i * 32 - m_nH;
					m_fDy = -0.1f; direction = rand() % (3); //����������� �������� ����� �� Y 
					}

					if (m_fDy < 0) 
					{ m_fY = i * 32 + 32;
					m_fDy = 0.1f; direction = rand() % (3);//����������� �������� ����� ������������ � �������� ������ 
					}

					if (m_fDx > 0) 
					{ m_fX = j * 32 - m_nW;
					m_fDx = -0.1f; direction = rand() % (3);//����������� �������� ����� � ������ ����� ����� 
					} 
					
					if (m_fDx < 0) 
					{ m_fX = j * 32 + 32;
					m_fDx = 0.1f; direction = rand() % (3); //����������� �������� ����� � ����� ����� ����� 
					}
					}
			*/
	for(unsigned i = m_fY/32; i < (m_fY+m_nH)/32; i++)
		for(unsigned j = m_fX/32; j < (m_fX+m_nW)/32; j++) {
			if(m_pszMapCode[i][j] == '0') {
				if(fDy > 0) {
					m_fY = i*32 - m_nH;
					m_fDy = 0.f; direction = rand() % (3);
				} else if(fDy < 0) {
					m_fY = i*32 + 32;
					m_fDy = 0.f; direction = rand() % (3);
				} else if(fDx > 0) {
					m_fX = j*32 - m_nW;
					m_fDx = 0.f; direction = rand() % (3); 
				} else if(fDx < 0) {
					m_fX = j*32 + 32;
					m_fDx = 0.f; direction = rand() % (3);
				}

			}
		}
}

	//bool  m_bLife;
	//int   m_nW, m_nH, m_nHealth;
	//float m_fX, m_fY, m_fDx, m_fDy;
	//float m_fSpeed, m_fCurrFrame;
	//sf::Sprite  m_Sprite;

void CEnemy::Frame(float& fTime) {
		//if (szName == "Army")
		//{ //��� ��������� � ����� ������ ������ ����� ����� 
		//	if (m_bLife) {//���������, ��� �� ����� 

				switch (direction) //�������� ��������� �������� � ����������� �� ��������� 
				{ 

				case RIGHT: {//��������� ���� ������ 
					m_fDx = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 192, 96, 96)); 
					break; } 
			
				case LEFT:	{//��������� ���� ����� 
					m_fDx = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 96, 96, 96));
					break; } 
				
				case UP:	{//���� ����� 
					m_fDy = -m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 288, 96, 96));
					break; }
				
				case DOWN:	{//���� ���� 
					m_fDy = m_fSpeed;
					m_fCurrFrame += 0.005*fTime;
					if (m_fCurrFrame > 3) m_fCurrFrame -= 3;
					m_Sprite.setTextureRect(IntRect(96 * int(m_fCurrFrame), 0, 96, 96));
					break; } 
			} // end switch

			m_fX += m_fDx*fTime; //�������� �� �X�
			checkCollisionWithMap(m_fDx, 0);//������������ ������������ �� � 
			m_fY += m_fDy*fTime; //�������� �� �Y� 
			checkCollisionWithMap(0, m_fDy);//������������ ������������ �� Y 
			m_Sprite.setPosition(m_fX, m_fY); //������ � ������� (x, y). 

		//	if (m_nHealth <= 0)
		//		{ m_bLife = false; }//���� ������ ������ 0, ���� ����� 0, �� ������� 
		//	} // end if life
		//}  // end if Army
	} // update