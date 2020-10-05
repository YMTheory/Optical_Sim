import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import uproot as up

def gaus(x, A, mu, sigma):
    return A*np.exp(-(x-mu)*(x-mu)/2/sigma/sigma)

def fitHist(inputfile, nbins, low, high):
    ff = up.open(inputfile)
    nphoton = ff["photon"].array("nPhoton")
    cont, bins = np.histogram(nphoton, bins=nbins, range=(low, high))
    bincenter = []
    for i in range(len(bins)-1):
        bincenter.append( (bins[i] + bins[i+1])/2. ) 
    popt, pcov = curve_fit(gaus, bincenter, cont, p0=(100, nphoton.mean(), np.std(nphoton)));
    
    return popt[1]
    #fity = []
    #for i in range(len(bincenter)):
    #    fity.append(gaus(bincenter[i], popt[0], popt[1], popt[2]))
    #plt.plot(bincenter, cont, "-")
    #plt.plot(bincenter, fity, "--")
    #plt.show()


plt.style.use("ggplot")

if __name__ == "__main__":
    filelist = []
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/rindex10.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/rindex11.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/rindex12.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/rindex13.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/rindex14.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/rindex15.root")
    nbins = [50, 50, 50, 50, 50, 50];
    nlow  = [5400, 4400, 3700, 3100, 2600, 2200];
    nhigh = [5800, 4800, 4100, 3500, 3000, 2600];
    rindex = [1, 1.1, 1.2, 1.3, 1.4, 1.5]

    nphoton_arr = []
    flag = 0; ref = 1;
    for name, nb, nl, nh in zip(filelist, nbins, nlow, nhigh):
        print(name)
        nphoton_arr.append( fitHist(name, nb, nl, nh) )
        if flag == 0:
            ref = nphoton_arr[-1]
            flag = 1


    plt.plot(rindex, np.array(nphoton_arr)/ref, "o-", ms=3, label='G4 sim')
    plt.plot(rindex, 1./np.array(rindex)**2, "s--", ms=3, label=r"$1/n^{2}$")
    plt.legend(); plt.xlabel("rindex"); plt.ylabel("nphoton ratio")
    plt.show()
