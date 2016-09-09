# UnblockScreenshot

Got black screenshot ? What the fuck ?

# DLL Patching

Just patch the function

Add user32.dll to HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\ExcludeFromKnownDlls, copy user32.dll to target application folder.

You can also replace your system user32.dll , but it may break your system.

# DLL Inject

Inject to target process

for some "M$ Signature Only" process , inject your injector to taskmgr , and use taskmgr to inject target process ( Manual Map or APC)

You can add to AppInit_dlls to load it in every process
