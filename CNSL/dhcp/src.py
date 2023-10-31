import subprocess

host = '192.168.1.39'
user = 'pi'
cmd = 'sudo apt-get install neofetch -y'

try:

    sshCmd = f'ssh {user}@{host} "{cmd}"'

    subprocess.check_call(sshCmd, shell=True)

    print("Neofetch has been successfully installed on the remote system.")

except subprocess.CalledProcessError as e:
    print(f"Installation failed with error code {e.returncode}.\nError message: {e.output}")

except Exception as e:
    print(f"An error occurred: {str(e)}")