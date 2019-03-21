#ifndef Landscape_H
#define Landscape_H

#include <Ogre.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

namespace RAT
{

// ��������� �������
struct LandscapeSettings
{
		// ��� ����� �����. ����� ������ ���� � ������� RAW.
	Ogre::String heightRawMap;
		// ������ ����� ����� �� ������ � ������ (size x size).
	int size;
		// ������� �� ������ � �����
	Ogre::Real scaleXZ;
		// ������� �� ������
	Ogre::Real scaleY;
		// �������� �����, ���������� ��������.
	Ogre::Light* light;
		// ������ ��������, � ������� �������� heightRawMap
	Ogre::String resourceGroup;

	int minBatchSize;

	int maxBatchSize;

		// ���� � ������� �������� ���������������� ��������, ���� ����� ���, 
		// �� �������� ������������� � ����������� � ���� ����. �������� ��������. ������������, ���� compiledTerrain != ""
	Ogre::String compiledTerrain;

        LandscapeSettings()
	: heightRawMap("terrain.raw")
	, size(256)
	, scaleXZ(1.0f)
	, scaleY(1.0f)
	, light(0)
	, resourceGroup(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME)
	, minBatchSize(33)
	, maxBatchSize (65)
	, compiledTerrain("")
	{
	}
};



	// ��������, � �������������� ����� ����� � ������� .raw � ������ ������� float ( 4 ����� )
class Landscape : public Ogre::FrameListener
{
public:

	
	Landscape();
	~Landscape();

	/** �������������
		@param settings - ��������� �������.
	*/
	void init(const LandscapeSettings& settings);

	/** ��������� ���� � ���������. ������������ ���������� ����� - 4.
		@param diffuseSpecularMap - ��� ��������, ���������� � RGB - diffuse ������������, � � ����� ������ - Specular.
		@param normalHeightMap - ��� ��������, ���������� ����� ����� ������� ����.
		@param blendMap - ��� ��������[������� ������] ���������� �������� ��������� � ������� ������.
		@param worldSize - ������ �� ������� ������������� ��������
	*/
	void addLayer(const Ogre::String& diffuseSpecularMap, const Ogre::String& normalHeightMap, const Ogre::String& blendMap, int worldSize); 

	/** ������� ��������. */
	void create(); 

	/** ������� ������ ��������� */
	void setupPhysics(float restitution = 0.6f, float friction = 0.6f); 

	/** ���������� ��������� �� ����� �������� */
	Ogre::Terrain* getTerrain();

protected:

	protected:
 
    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	Ogre::Terrain* mTerrain;
	Ogre::Terrain::ImportData	mImportData;
	LandscapeSettings			mSettings;
	std::vector<Ogre::String>	mBlendImages;
	bool						mUseBinary;

        Ogre::Vector3 mVector3;
    Ogre::TerrainGroup* mTerrainGroup;

};

}

#endif
