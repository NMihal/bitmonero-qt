DEPRECATED README

bitmonero-qt
============

Monero GUI Wallet


**DISCLAIMER : This is not an official Wallet for Monero. Use this software at your own risk.**


Current status : Testing



Using a Monero GUI wallet should be reserved to experienced users at this stage.
The Monero core itself is in perpetual improvement but not yet ready of end users.
Please use with caution.


Dependencies
------------

The project is based on **Qt** SDK. It should work version **5.2+**.
* Arch-based distributions : `sudo pacman -S qt5`

* Debian-based distributions : `sudo apt-get install qt5-default qttools5-dev-tools`
    
* Or try the **Qt**'s installer : [http://qt-project.org/downloads]


Compiling
---------

    git clone https://github.com/Neozaru/bitmonero-qt.git
    cd bitmonero-qt
    qmake
    make

The app will be installed in `./app/bitmonero-qt`


Usage
-----

**Monero Wallet** depends on core **bitmonerod** and **simplewallet**. These two programs should be installed in same folder as bitmonero-qt or in $HOME/.bitmonero-qt/


#### Running *bitmonero-qt*

Ensure that NO *bitmonerod* or *simplewallet* processes are already running, and do :

    ./app/bitmonero-qt


By default, **bitmonero-qt** will connect to daemons ports 18081 (*bitmonerod*) and 19091 (*simplewallet*).


Your can change the configuration with the file `$HOME/.bitmonero-qt/bitmonero-qt.conf`


Configuration file example for using existing bitmonerod process
----------------------------------------------------------------
    
    [General]

    # These values are defaults
    daemon_uri=http://localhost/json_rpc
    daemon_port=18081

    # Wallet auto-spawn. Settings will depend on your own system.
    daemon_program=/home/myself/gitcode/bitmonero/bitmonerod
    

Available features
------------------
* Create/Import Wallet wizard
* Overview (balance, address)
* Transfer (choose an amount and a recipient. Optional payment ID and custom fee)
* Mining (choose number of threads and your address, and start mining)


Limitations
-----------
* Transactions history is not (yet) available.
* Mining interface can get confused if mining is started from somewhere else


Roadmap
-------
* Bitmonero C++ integration (all-in-one)
* Advanced interface

Alternatives
------------

* CryptoNote Wallet ('.NET' based) : [https://github.com/BitKoot/CryptoNoteWallet]
* cryptonoteRPCwalletGUI ('python-kivy' based) : [https://github.com/jwinterm/cryptonoteRPCwalletGUI]
