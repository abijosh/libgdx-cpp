/*
 * ObjLoader.h
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include "gdx-cpp/graphics/g3d/loaders/StillModelLoader.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include <algorithm>

using namespace std;
using namespace gdx;

namespace gdx {

class ObjLoader : public StillModelLoader
{
private:
	class Group
	{
	friend class ObjLoader;
	private:
		string name;
		string materialName;
		vector<int> faces;
		int numFaces;
		bool hasNorms;
		bool hasUVs;
		Material mat;

	public:
		Group(string name) {
			this->name = name;
			numFaces = 0;
			hasNorms = false;
			hasUVs = false;
			materialName = "default";
		}
	};
	
	class MtlLoader {
	private:
		vector<Material> materials;
		//static AssetManager
		static Texture* emptyTexture;
	public:
		MtlLoader();
		void load(string fileName, FileHandle& textureDir);
	};
	
	vector<float> verts;
	vector<float> norms;
	vector<float> uvs;
	vector<Group> groups;
	Group setActiveGroup(const string& group);
	int getIndex(string index, int size);
	
	void proccessVerteOrNormal(string& line, const char* templ, vector<float>& container);
	void proccessUV(string& line, bool isFlip);
public:

	ObjLoader();
	virtual ~ObjLoader();
	StillModel* loadObj(const FileHandle& file, bool flipV = false);
	StillModel* loadObj(const FileHandle& file, FileHandle& textureDir, bool flipV);
	StillModel* load(const FileHandle& handle, ModelLoaderHints hints);
};

}

#endif /* OBJLOADER_H_ */
