/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Sun Sep 27 17:12:30 2020
 @File Name: B1ParticleSource.hh
 ************************************************************************/

#ifndef B1ParticleSource_h
#define B1ParticleSource_h 1


#include "G4VPrimaryGenerator.hh"
#include "G4ParticleMomentum.hh"
#include "G4ParticleDefinition.hh"

#include "B1ParticleSourceMessenger.hh"

class B1ParticleSource : public G4VPrimaryGenerator {

    public:
        B1ParticleSource   ();
        ~B1ParticleSource  ();
    
        void GeneratePrimaryVertex(G4Event* event);

    public:
        // particle number
        void SetParticleNumber(G4int);

        // position distribution
        void SetPosDisType(G4String);
        void SetPosDisShape(G4String);
        void SetCentreCoords(G4ThreeVector);
        void SetSourceLength(G4double);
        void GeneratePointSource();
        void GenerateLineSource();

        // angular distribution
        void SetAngDistType(G4String);
        void SetAngLimit(G4double);
        void SetParticleMomentumDirection(G4ParticleMomentum);
        void GenerateIsotropicFlux();
        void GenerateHalfSphere();
        void GenerateCustomAngle();

        // energy distribution
        void SetEnergyDisType(G4String);
        void SetMonoEnergy(G4double);
        inline G4double GetParticleEnergy() { return particle_energy; }
        void GenerateMonoEnergetic();

        // verbosity
        void SetVerbosity(G4int);

        // particle properties
        void SetParticleDefinition(G4ParticleDefinition* aParticleDefinition);

        
    private:
        // position distribution
        G4String                SourcePosType;
        G4String                Shape;
        G4ThreeVector           CentreCoords;
        G4double                SourceLength;
        
        // angular distribution
        G4String AngDistType;
        G4double MinTheta, MaxTheta, MinPhi, MaxPhi;
        G4double Phi;
        G4double custom_angle;

        // energy distribution
        G4String EnergyDisType;
        G4double MonoEnergy;

        // particle properties
        G4int                   NumberOfParticlesToBeGenerated;
        G4ParticleDefinition*   particle_definition;
        G4ParticleMomentum      particle_momentum_direction;
        G4double                particle_energy;
        G4ThreeVector           particle_position;
        G4double                particle_time;
        G4ThreeVector           particle_polarization;
    
        //std::vector<G4double>   vec_particle_y;

        // Verbose
        G4int verbosityLevel;

    private:
        B1ParticleSourceMessenger* theMessenger;
};

#endif
