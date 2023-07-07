#ifndef ___DEBUG_H___
#define ___DEBUG_H___

namespace nhs
{
	/*・機能：デバッガに文字列を出力
	　　デバッグ出力ウィンドウに文字列を直接送信する							*/
	void DebugLog(const char* format, ...);
}

#endif //!___DEBUG_H___