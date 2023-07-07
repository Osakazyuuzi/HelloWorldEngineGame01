#ifndef ___DEFINE_H___
#define ___DEFINE_H___

namespace nhs
{
	/*・機能：対象のパラメータを文字列に変換させる
		期待通りの挙動をしない場合は STRINGIZE を使用してください				*/
	#define STRINGIZE_HELPER(x) #x
	#define STRINGIZE(x) STRINGIZE_HELPER(x)

	/*・機能：対象のトークンを連結させる
		期待通りの挙動をしない場合は CONCAT を使用してください					*/
	#define CONCAT_HELPER(x,y) x##y
	#define CONCAT(x,y) CONCAT_HELPER(x,y)

	/*・機能：安全にdeleteする
	　　nullptrかどうかをチェックし、必要に応じてdeleteしてnullptrを代入する	*/
	template <class T>
	inline void SAFE_DELETE(T*& p) {
		if (p) {
			delete p;
			p = nullptr;
		}
	}
}

#endif //!___DEFINE_H___