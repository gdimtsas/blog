import { ethers } from "hardhat";
import chai from "chai";
import chaiAsPromised from "chai-as-promised";

import { TutorialToken } from "../typechain/TutorialToken";
import { TutorialToken__factory } from "../typechain/factories/TutorialToken__factory";
import { Signer } from "ethers";

chai.use(chaiAsPromised);
const { expect } = chai;

describe("TutorialToken", () => {
  let tutorialTokenFactory: TutorialToken__factory;
  let tutorialToken: TutorialToken;

  describe("Deployment", () => {
    let deployer: Signer;

    beforeEach(async () => {
      [deployer] = await ethers.getSigners();
      tutorialTokenFactory = new TutorialToken__factory(deployer);
      tutorialToken = await tutorialTokenFactory.deploy(100);
      await tutorialToken.deployed();
    });

    it("should have the correct name", async () => {
      expect(await tutorialToken.name()).to.equal("Tutorial");
    });

    it("should have the correct symbol", async () => {
      expect(await tutorialToken.symbol()).to.equal("TUT");
    });

    it("should have the correct total supply", async () => {
      expect((await tutorialToken.totalSupply()).toString()).to.equal("100");
    });

    it("should have correct balance after deployment", async () => {
      expect(await tutorialToken.balanceOf(await deployer.getAddress())).to.equal("100");
    });
  });
});
