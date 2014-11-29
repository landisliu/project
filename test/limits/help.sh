ps aux|grep './main'|awk '{v= "kill -9 " $2;system(v)}'
