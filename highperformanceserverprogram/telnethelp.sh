#telnet
#sudo arp -d 192.168.1.116
#sudo tcpdump -i wlan0 -ent '(dst 192.168.1.116 and src 192.168.1.115) or (dst 192.168.1.115 and src 192.168.1.116)'


#dns
#sudo tcpdump -i wlan0 -ntX -s 500 port domain

#ipv4
sudo tcpdump -netx -i wlan0

#ping
#sudo tcpdump -ntv -i wlan0 icmp 
