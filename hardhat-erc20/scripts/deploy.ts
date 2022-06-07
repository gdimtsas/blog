import { ethers } from "hardhat";

async function main() {

  const tutorialTokenFactory = await ethers.getContractFactory("TutorialToken");
  const tutorialToken = await tutorialTokenFactory.deploy(ethers.utils.parseUnits("100"));

  await tutorialToken.deployed();

  console.log("TutorialToken deployed to:", tutorialToken.address);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
