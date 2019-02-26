#ifndef JLW_ENCRYPT_MAIN_H_
#define JLW_ENCRYPT_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

#if 0

#ifndef JLW_Verification_C_DLL
#define JLW_Verification_C_DLL _declspec(dllexport)
#else
#define JLW_Verification_C_DLL _declspec(dllimport)
#endif

	// 合法性验证接口，key路径不可更改，默认路径（./key.key）
	bool JLW_Verification_C_DLL JLW_Verification();

	// 合法性验证接口，key路径可更改，默认路径（./key.key）
	bool JLW_Verification_C_DLL JLW_VerificationEx(const char *keyPath = "./key.key");

#else

	// 合法性验证接口，key路径不可更改，默认路径（./key.key）
	bool JLW_Verification();

	// 合法性验证接口，key路径可更改，默认路径（./key.key）
	bool JLW_VerificationEx(const char *_keyFullPath = "./key.key");

#endif

#ifdef __cplusplus
}
#endif


#endif // JLW_ENCRYPT_MAIN_H_