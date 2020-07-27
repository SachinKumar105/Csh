all:	shell.c
		gcc -w shell.c bltcmds.c dis.c history.c ls.c envvar.c par.c pinfo.c cronjob.c jobs.c syscmd.c  -lreadline -o shell