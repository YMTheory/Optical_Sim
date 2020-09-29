/*************************************************************************
 @Author: MiaoYu ---> miaoyu@ihep.ac.cn
 @Created Time : Sun Sep 27 17:15:05 2020
 @File Name: B1ParticleSource.cc
 ************************************************************************/


#include "B1ParticleSource.hh"

#include "G4Event.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4PrimaryParticle.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

B1ParticleSource::B1ParticleSource ()  {

    NumberOfParticlesToBeGenerated = 10000; 
    particle_definition            = NULL;
    G4ThreeVector zero (0., 0., 0.);
    particle_momentum_direction    = G4ParticleMomentum(1., 0., 0.);
    particle_time                  = 0.0;
    particle_energy                = 1.0*MeV;
    particle_polarization          = G4ThreeVector(1., 0., 0.);

    SourcePosType                  = "Volume";
    Shape                          = "NULL";
    CentreCoords                   = zero;

    AngDistType                    = "iso";
    MinTheta                       = 0.;
    MaxTheta                       = pi;
    MinPhi                         = 0.;
    MaxPhi                         = twopi;
    custom_angle                   = pi/2.;

    EnergyDisType                  = "Mono";
    MonoEnergy                     = 1*MeV;

    theMessenger                   = new B1ParticleSourceMessenger(this);
}

B1ParticleSource::~B1ParticleSource () {
    delete theMessenger;
}


void B1ParticleSource::SetParticleNumber(G4int number) 
{
    NumberOfParticlesToBeGenerated = number;
}

void B1ParticleSource::SetPosDisType(G4String PosType)
{
    SourcePosType = PosType;
}

void B1ParticleSource::SetPosDisShape(G4String shapeType)
{
    Shape = shapeType;
}

void B1ParticleSource::SetCentreCoords(G4ThreeVector coordsOfCentre)
{
  CentreCoords = coordsOfCentre;
}

void B1ParticleSource::GeneratePointSource()
{
    if(SourcePosType == "Point" ) 
        particle_position = CentreCoords;
    else{
        if(verbosityLevel >= 1)
            G4cout << "Error SourcePosType is not set to Point" << G4endl;
    }
}


void B1ParticleSource::SetAngDistType(G4String atype) 
{
    AngDistType = atype;
}

void B1ParticleSource::SetAngLimit( G4double angle )
{
    custom_angle = angle;
}


void B1ParticleSource::SetParticleMomentumDirection
(G4ParticleMomentum aDirection)  {
    particle_momentum_direction = aDirection.unit();
}

void B1ParticleSource::GenerateIsotropicFlux()
{
    G4double rndm, rndm2;
    G4double px, py, pz;

    G4double sintheta, sinphi, costheta, cosphi;
    rndm = G4UniformRand();
    costheta = std::cos(MinTheta) - rndm * (std::cos(MinTheta) - std::cos(MaxTheta));
    sintheta = std::sqrt(1. - costheta*costheta);

    rndm2 = G4UniformRand();
    Phi = MinPhi + (MaxPhi - MinPhi) * rndm2; 
    sinphi = std::sin(Phi);
    cosphi = std::cos(Phi);

    px = -sintheta * cosphi;
    py = -sintheta * sinphi;
    pz = -costheta;

    G4double ResMag = std::sqrt((px*px) + (py*py) + (pz*pz));
    px = px/ResMag;
    py = py/ResMag;
    pz = pz/ResMag;

    particle_momentum_direction.setX(px);
    particle_momentum_direction.setY(py);
    particle_momentum_direction.setZ(pz);

    // particle_momentum_direction now holds unit momentum vector.
    if(verbosityLevel >= 2)
        G4cout << "Generating isotropic vector: " << particle_momentum_direction << G4endl;
}


void B1ParticleSource::GenerateHalfSphere()
{
    G4double rndm, rndm2;
    G4double px, py, pz;
    G4double sintheta, sinphi, costheta, cosphi;
    while(1) {
        rndm = G4UniformRand();
        costheta = std::cos(MinTheta) - rndm * (std::cos(MinTheta) - std::cos(MaxTheta));
        sintheta = std::sqrt(1. - costheta*costheta);

        rndm2 = G4UniformRand();
        Phi = MinPhi + (MaxPhi - MinPhi) * rndm2; 
        sinphi = std::sin(Phi);
        cosphi = std::cos(Phi);

        px = -sintheta * cosphi;
        py = -sintheta * sinphi;
        pz = -costheta;

        if( px < 0 ) continue;

        G4double ResMag = std::sqrt((px*px) + (py*py) + (pz*pz));
        px = px/ResMag;
        py = py/ResMag;
        pz = pz/ResMag;

        particle_momentum_direction.setX(px);
        particle_momentum_direction.setY(py);
        particle_momentum_direction.setZ(pz);

        break;
    }
    // particle_momentum_direction now holds unit momentum vector.
    if(verbosityLevel >= 2)
        G4cout << "Generating half sphere vector: " << particle_momentum_direction << G4endl;
}


void B1ParticleSource::GenerateCustomAngle()
{

    G4double rndm, rndm2;
    G4double px, py, pz;
    G4double sintheta, sinphi, costheta, cosphi;
    while(1) {
        rndm = G4UniformRand();
        costheta = std::cos(MinTheta) - rndm * (std::cos(MinTheta) - std::cos(MaxTheta));
        sintheta = std::sqrt(1. - costheta*costheta);

        rndm2 = G4UniformRand();
        Phi = MinPhi + (MaxPhi - MinPhi) * rndm2; 
        sinphi = std::sin(Phi);
        cosphi = std::cos(Phi);

        px = -sintheta * cosphi;
        py = -sintheta * sinphi;
        pz = -costheta;

        G4double ResMag = std::sqrt((px*px) + (py*py) + (pz*pz));
        px = px/ResMag;
        py = py/ResMag;
        pz = pz/ResMag;

        if ( px <=0 ) continue;
        G4double m_angle = std::acos(px);
        if( m_angle>=custom_angle ) continue;

        particle_momentum_direction.setX(px);
        particle_momentum_direction.setY(py);
        particle_momentum_direction.setZ(pz);

        break;
    }
    // particle_momentum_direction now holds unit momentum vector.
    if(verbosityLevel >= 2)
        G4cout << "Generating half sphere vector: " << particle_momentum_direction << G4endl;


}



void B1ParticleSource::SetEnergyDisType(G4String DisType)
{
    EnergyDisType = DisType;
}

void B1ParticleSource::SetMonoEnergy(G4double menergy) 
{
    MonoEnergy = menergy;
}



void B1ParticleSource::GenerateMonoEnergetic()
{
    particle_energy = MonoEnergy;
}

void B1ParticleSource::SetVerbosity(G4int vL)
{
    verbosityLevel = vL;
    G4cout << " Verbosity Level Set to : " << verbosityLevel << G4endl;
}


void B1ParticleSource::SetParticleDefinition(G4ParticleDefinition* aParticleDefinition)
{
    particle_definition = aParticleDefinition;
}


void B1ParticleSource::GeneratePrimaryVertex(G4Event* event)  {
    if( particle_definition == NULL ) {
        G4cout << "No particle has been defined !" << G4endl;
        return;
    }

    for( G4int i=0; i<NumberOfParticlesToBeGenerated; i++ ) {
        // Position
        if( SourcePosType == "Point" ) {
            GeneratePointSource();
        } else {
            G4cout << "Error:: SourcePosType undefined" << G4endl;
            G4cout << "Generating point source" << G4endl;
            GeneratePointSource();
        }


        // Angular Stuff
        if(AngDistType == "iso" )
            GenerateIsotropicFlux();
        else if( AngDistType == "HalfSphere" )
            GenerateHalfSphere();
        else if( AngDistType == "direction" )
            SetParticleMomentumDirection(particle_momentum_direction);
        else if ( AngDistType == "custom" )
            GenerateCustomAngle();


        // Energy Stuff
        if(EnergyDisType == "Mono" )
            GenerateMonoEnergetic();
        else
            G4cout << "Error: EnergyDisType has unusual value" << G4endl;


        // create a new verbosityLevel
        G4PrimaryVertex* vertex = new G4PrimaryVertex(particle_position, particle_time);
        if(verbosityLevel >= 2)
            G4cout << "Creating primaries and assigning to vertex" << G4endl;
        G4double mass   = 0.;   // optical photon
        G4double energy = particle_energy;
        G4double pmom   = std::sqrt(energy*energy - mass*mass);
        G4double px     = pmom*particle_momentum_direction.x();
        G4double py     = pmom*particle_momentum_direction.y();
        G4double pz     = pmom*particle_momentum_direction.z();
        if(verbosityLevel >= 2){
            G4cout << "Particle name: " 
                << particle_definition->GetParticleName() << G4endl; 
            G4cout << "       Energy: "<<particle_energy << G4endl;
            G4cout << "     Position: "<<particle_position<< G4endl; 
            G4cout << "    Direction: "<<particle_momentum_direction << G4endl;
            G4cout << " NumberOfParticlesToBeGenerated: "
                << NumberOfParticlesToBeGenerated << G4endl;
        }

        G4PrimaryParticle* particle =
            new G4PrimaryParticle(particle_definition,px,py,pz);
        particle->SetMass( mass );
        //particle->SetCharge( particle_charge );
        particle->SetPolarization(particle_polarization.x(),
                particle_polarization.y(),
                particle_polarization.z());
        vertex->SetPrimary( particle );
        event->AddPrimaryVertex( vertex );
    }
    if(verbosityLevel > 1)
        G4cout << " Primary Vetex generated "<< G4endl;   


}
