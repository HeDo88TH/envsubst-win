# envsubst-win
Replaces environment variables in template file. 

I know this could be done with some contrived bash/powershell but it works so well and clean on linux that i HAD TO build this from scratch.

Usage: `envsubst-win.exe templatefile destfile`

It replaces the variables like `$variable` in template and writes it in output file, example:

```bash
{
	"processor": "$PROCESSOR_IDENTIFIER"
}
```

to

```bash
{
	"processor": "AMD64 Family 25 Model 33 Stepping 0, AuthenticAMD"
}
```
