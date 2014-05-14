Set objShell = WScript.CreateObject("WScript.Shell")
Set colSystemEnvVars = objShell.Environment("System")
Set colUserEnvVars = objShell.Environment("User")
Wscript.Echo "Computer-specific PATH Environment Variable"
Wscript.Echo colSystemEnvVars("PATH")
Wscript.Echo "User-specific PATH Environment Variable"
Wscript.Echo colUserEnvVars("PATH")