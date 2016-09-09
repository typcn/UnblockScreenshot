# UnblockScreenshot

Got black screenshot ? What the fuck ?

# DLL Patching

Just patch the function

Add user32.dll to HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\ExcludeFromKnownDlls, copy user32.dll to target application folder.

# DLL Inject

Inject to target process

for some "M$ Signature Only" process , inject your injector to taskmgr , and use taskmgr to inject target process ( Manual Map or APC)
