import type { NextPage } from "next";
import Head from "next/head";
import { VStack, HStack, Heading, Box } from "@chakra-ui/layout";
import { Button, Flex, Spacer, Divider, Stat, StatLabel, StatNumber, StatHelpText, Badge } from "@chakra-ui/react";

import { useState, useEffect } from "react";
import { ethers } from "ethers";
import { Web3Provider } from "@ethersproject/providers";

declare const window: any;

const Home: NextPage = () => {
  const [balance, setBalance] = useState<string | undefined>();
  const [currentAccount, setCurrentAccount] = useState<string | undefined>();
  const [chainId, setChainId] = useState<number | undefined>();
  const [chainName, setChainName] = useState<string | undefined>();

  useEffect(() => {
    if (!currentAccount || !ethers.utils.isAddress(currentAccount)) return;

    if (!window.ethereum) {
      console.log("please install MetaMask");
      return;
    }

    const provider = new ethers.providers.Web3Provider(window.ethereum);

    fetchChainInfo(provider);
    fetchBalance(provider);

    // remove all listeners when the component is unmounted
    return () => {
      provider.removeAllListeners();
    };
  }, [currentAccount, chainId]);

  function fetchBalance(provider: Web3Provider) {
    if (!currentAccount) return;

    provider.getBalance(currentAccount).then((balance) => {
      setBalance(ethers.utils.formatEther(balance));
    });
  }

  function fetchChainInfo(provider: Web3Provider) {
    provider.getNetwork().then((network) => {
      setChainId(network.chainId);
      setChainName(network.name);
    });
  }

  const connect = () => {
    if (!window.ethereum) {
      console.log("please install MetaMask");
      return;
    }

    const provider = new ethers.providers.Web3Provider(window.ethereum);

    window.ethereum.on("accountsChanged", onAccountChanged);

    window.ethereum.on("chainChanged", onChainChanged);

    provider
      .send("eth_requestAccounts", [])
      .then((accounts) => {
        if (accounts.length > 0) setCurrentAccount(accounts[0]);
      })
      .catch((e) => console.log(e));
  };

  const disconnect = () => {
    setBalance(undefined);
    setCurrentAccount(undefined);
  };

  const onAccountChanged = (accounts: Array<string>) => {
    const provider = new ethers.providers.Web3Provider(window.ethereum);
    setCurrentAccount(accounts[0]);
    fetchBalance(provider);
  };

  const onChainChanged = () => {
    const provider = new ethers.providers.Web3Provider(window.ethereum);
    fetchChainInfo(provider);
    fetchBalance(provider);
  };

  return (
    <>
      <Head>
        <title>My DAPP</title>
      </Head>
      <Flex>
        <Spacer />
        <VStack w="35em">
          <Spacer />
          <Box w="100%">
            {currentAccount ? (
              <Button colorScheme="green" type="button" w="100%" onClick={disconnect}>
                {currentAccount}
              </Button>
            ) : (
              <Button colorScheme="red" type="button" w="100%" onClick={connect}>
                Connect MetaMask
              </Button>
            )}
          </Box>
          {currentAccount ? (
            <Box mb={0} p={4} w="100%" borderWidth="1px" borderRadius="lg">
              <Heading my={4} fontSize="xl">
                Account info
              </Heading>
              <Divider />
              <Stat>
                <StatLabel>Balance</StatLabel>
                <StatNumber>Ξ {balance}</StatNumber>
                <StatHelpText>
                  <HStack spacing="10px">
                    <Badge colorScheme="green" variant="outline">
                      {chainId}
                    </Badge>
                    <Badge colorScheme="blue" variant="outline">
                      {chainName}
                    </Badge>
                  </HStack>
                </StatHelpText>
              </Stat>
            </Box>
          ) : (
            <></>
          )}
        </VStack>
        <Spacer />
      </Flex>
    </>
  );
};

export default Home;
