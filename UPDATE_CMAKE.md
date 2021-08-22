**A-1.** Uninstall the default version provided by Ubuntu's package manager and configuration by using:
```sh
sudo apt remove --purge --auto-remove cmake
```
or:
```sh
sudo apt purge --auto-remove cmake
```

**A-2.** Prepare for installation
```sh
sudo apt update && \
sudo apt install -y software-properties-common lsb-release && \
sudo apt clean all
```

**A-3.** Obtain a copy of kitware's signing key.
```sh 
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
```

**A-4.** Add kitware's repository to your sources list for Ubuntu Focal Fossa (20.04), Ubuntu Bionic Beaver (18.04) and Ubuntu Xenial Xerus (16.04).
```sh 
sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
```

**A-5.** As an optional step, is recommended that we also install the `kitware-archive-keyring` package to ensure that Kitware's keyring stays up to date as they rotate their keys.
```sh
sudo apt update
sudo apt install kitware-archive-keyring
sudo rm /etc/apt/trusted.gpg.d/kitware.gpg
```

**A-6.** Finally we can update and install the `cmake` package.
```sh 
sudo apt update
sudo apt install cmake
