{
  description = "logic-and-formalization";

  inputs = {
    nixpkgs = {
      owner = "NixOS";
      repo = "nixpkgs";
      rev = "ce35e61c3cc608d0f7c4a5ed96f7fb3c19211884";
      type = "github";
    };
    flake-utils = {
      owner = "numtide";
      repo = "flake-utils";
      rev = "93a2b84fc4b70d9e089d029deacc3583435c2ed6";
      type = "github";
    };
    satyxin = {
      owner = "SnO2WMaN";
      repo = "satyxin";
      rev = "b3420b0b66b63ff84ded127beb18a57647bba205";
      type = "github";
    };
  };

  outputs = {
    self
  , nixpkgs
  , flake-utils
  , satyxin
  }: 
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ 
            satyxin.overlays.default
          ];
        };
        filename = week-num: "第${toString week-num}回_浅田睦葉_202210897.pdf";
        buildDocument = week-num: pkgs.satyxin.buildDocument {
          satysfiDist = self.packages.${system}.satysfiDist;
          name = filename week-num;
          src = ./src;
          entrypoint = "week${toString week-num}.saty";
          output = filename week-num;
        };
      in rec {
        packages = rec {
          satysfiDist = pkgs.satyxin.buildSatysfiDist {
            packages = with pkgs.satyxinPackages; [
              derive
              figbox
            ];
          };
        };
      }
    );
}
