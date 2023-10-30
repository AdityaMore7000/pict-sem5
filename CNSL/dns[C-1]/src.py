import socket

def ip_to_url(ip_address):
    try:
        url = socket.gethostbyaddr(ip_address)
        return url[0]
    except socket.herror:
        return "Could not resolve the IP to a URL."

def url_to_ip(url):
    try:
        ip = socket.gethostbyname(url)
        return ip
    except socket.gaierror:
        return "Could not resolve the URL to an IP address."

def main():
    while True:
        print("Enter 1 to convert IP to URL")
        print("Enter 2 to convert URL to IP")
        print("Enter 3 to exit")
        choice = input("Enter your choice: ")

        if choice == '1':
            ip_address = input("Enter IP address: ")
            print("URL: ", ip_to_url(ip_address))
        elif choice == '2':
            url = input("Enter URL: ")
            print("IP address: ", url_to_ip(url))
        elif choice == '3':
            break
        else:
            print("Invalid choice")

if __name__ == '__main__':
    main()