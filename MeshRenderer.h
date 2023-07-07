#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include <memory>
#include "ConstantBuffer.h"
#include "ComponentBase.h"
#include "DirectXTex/Texture.h"
#include <list>

class MeshRenderer : public ComponentBase
{
public:
	// 定数
	using NodeIndex = int;
	using AnimeNo = int;
	static const NodeIndex		INDEX_NONE = -1;
	static const AnimeNo		ANIME_NONE = -1;
	static const AnimeNo		ANIME_PARAMETRIC = -2;
	static const unsigned int	MAX_BONE = 50; // ここを変更する場合、.hlsl側の定数も変更する
	enum AnimeTransformKind
	{
		ANIME_TRANSFORM_MAIN,
		ANIME_TRANSFORM_BLEND,
		ANIME_TRANSFORM_PARAMETRIC0,
		ANIME_TRANSFORM_PARAMETRIC1,
		MAX_ANIME_TRANSFORM
	};

	//--- 各種データ定義
private:
	using Children = std::vector<NodeIndex>;
	using Mapping = std::map<std::string, NodeIndex>;
	using MappingKey = std::pair<std::string, NodeIndex>;
	// 3値のアニメーションキー
	struct Key3
	{
		float				time;
		DirectX::XMFLOAT3	value;
	};
	using KeyFrames3 = std::vector<Key3>;
	// 4値のアニメーションキー
	struct Key4
	{
		float				time;
		DirectX::XMFLOAT4	value;
	};
	using KeyFrames4 = std::vector<Key4>;
	// アニメーションキーフレーム
	struct Channel
	{
		NodeIndex	index;
		KeyFrames3	pos;
		KeyFrames4	quat;
		KeyFrames3	scale;

	};
	using Channels = std::vector<Channel>;

	// アニメーション情報
	struct Animation
	{
		float		time;		// 現在の再生時間
		float		totalTime;	// アニメーションの長さ
		float		speed;		// 再生速度
		bool		isLoop;		// ループ設定
		Channels	channels;	// キーフレーム情報
	};
	using Animations = std::vector<Animation>;
public:
	// 
	struct meshTransform
	{
		DirectX::XMFLOAT3 translate;
		DirectX::XMFLOAT4 quaternion;
		DirectX::XMFLOAT3 scale;
	};
	using NodeTransforms = std::vector<meshTransform>;
	// 階層構造
	struct Node
	{
		std::string			name;		// ノード名
		NodeIndex			parent;		// 親
		Children			children;	// 子要素
		DirectX::XMFLOAT4X4	offset;		// ノードオフセット値
		DirectX::XMMATRIX	mat;		// 計算済みノード行列
	};
	using Nodes = std::vector<Node>;
public:
	// 頂点情報
	struct Vertex
	{
		DirectX::XMFLOAT3	pos;		// 座標
		DirectX::XMFLOAT3	normal;		// 法線
		DirectX::XMFLOAT2	uv;			// テクスチャ座標
		float				weight[4];	// 頂点ブレンドウェイト
		unsigned int		index[4];	// 頂点ブレンドインデックス
	};
	// マテリアル
	struct Material
	{
		DirectX::XMFLOAT4			diffuse;	// 拡散光
		DirectX::XMFLOAT4			ambient;	// 環境光
		DirectX::XMFLOAT4			specular;	// 鏡面反射光
		ID3D11ShaderResourceView*	pTexture;	// テクスチャ
	};
	// 
	struct Bone
	{
		NodeIndex			index;
		DirectX::XMFLOAT4X4	invOffset;
	};
	// メッシュ情報
	struct Mesh
	{
		Vertex*			pVertices;	// 頂点情報
		unsigned int	vertexNum;	// 頂点数
		unsigned int*	pIndices;	// インデックス情報
		unsigned int	indexNum;	// インデックス数
		unsigned int	materialID;	// 割り当てるマテリアル
		Bone*			pBones;		// ボーン情報
		unsigned int	boneNum;	// ボーン数
		MeshBuffer*		pMesh;		// 頂点バッファ
	};

	struct Info {
		Mesh* m_pMeshes;
		unsigned int m_meshNum;
		Material* m_pMaterials;
		unsigned int m_materialNum;
	};

public:
	MeshRenderer();
	~MeshRenderer();

	bool LoadModel(const char* file, float scale, bool flip = false);

	void Start();
	void LateUpdate();
	void Draw();

	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);
	const Mesh* GetMesh(unsigned int index);
	unsigned int GetMeshNum();

	void SetColor(DirectX::XMFLOAT3 _color);

	AnimeNo AddAnimation(const char* file);
	void Step(float tick);

	void Play(AnimeNo no, bool loop);
	void PlayBlend(AnimeNo no, float blendTime, bool loop);
	void SetParametric(AnimeNo no1, AnimeNo no2);
	void SetParametricBlend(float blendRate);

	bool IsPlay(AnimeNo no);
	AnimeNo GetPlayNo();
	AnimeNo GetBlendNo();
	float GetRemainingTime(AnimeNo no);

private:
	void MakeNodes(const void* pScene);
	void MakeBoneWeight(const void* scene, int i);
	void UpdateBoneMatrix(int i);
	bool AnimeNoCheck(AnimeNo no);
	void InitAnime(AnimeNo no);
	void UpdateAnime(AnimeNo no, float tick);
	void CalcBones(NodeIndex index, DirectX::XMMATRIX parent);
	void CalcAnime(AnimeTransformKind kind, AnimeNo no);
	DirectX::XMFLOAT3 Lerp(DirectX::XMFLOAT3& a, DirectX::XMFLOAT3& b, float rate);
	DirectX::XMFLOAT4 Lerp(DirectX::XMFLOAT4& a, DirectX::XMFLOAT4& b, float rate);

private:
	static VertexShader* m_pDefVS;
	static PixelShader* m_pDefPS;
	static PixelShader* m_pLambertPS;
	static PixelShader* m_pPhongPS;
	static PixelShader* m_pToonPS;
	static unsigned int m_shaderRef;
	// モデルリスト
	static std::list<std::pair<std::string, Info*>> m_ModelList;
private:
	float			m_modelScale;
	bool			m_isModelFlip;
	Nodes			m_nodes;
	Mapping			m_boneMapping;
	Mesh*			m_pMeshes;
	unsigned int	m_meshNum;
	Material*		m_pMaterials;
	unsigned int	m_materialNum;
	VertexShader*	m_pVS;
	PixelShader*	m_pPS;
	ConstantBuffer*	m_pBones;
	Animations		m_animes;
	AnimeNo			m_playNo;
	AnimeNo			m_blendNo;
	float			m_blendTime;
	float			m_blendTotalTime;
	AnimeNo			m_parametric[2];
	float			m_parametricBlend;
	NodeTransforms	m_animeTransform[MAX_ANIME_TRANSFORM];
	std::shared_ptr<ConstantBuffer> m_pWVP;
	DirectX::XMFLOAT4X4 m_Mat[3];

	// シェーダーに送るモデルの情報
	struct ModelInfoCb {
		// モデルの色
		DirectX::XMFLOAT3 m_ModelColor;
		// パディング
		float padding;
	};
	ModelInfoCb m_ModelInfoCb;
	// モデルの情報を送るバッファ
	std::shared_ptr<ConstantBuffer> m_pModelInfoCb;
};


#endif // __SPRITE_H__
