import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import uproot as up
from ROOT import TH1D, TF1, TMath
import math

def gaus(x, A, mu, sigma):
    return A*np.exp(-(x-mu)*(x-mu)/2/sigma/sigma)

def fitHist(inputfile, nbins, low, high):
    ff = up.open(inputfile)
    nphoton = ff["photon"].array("nPhoton")
    # Use ROOT fitting
    temph = TH1D("temph",  "", nbins, low, high)
    for elem in nphoton:
       temph.Fill(elem) 
    gaus = TF1("gaus", "gaus", low, high)
    temph.Fit(gaus, "REQ0")

    return gaus.GetParameter(1), gaus.GetParError(1)

# Cn factor from Carr and Zimm
def CnFormula(n):
    r1 = 6.26  # mm
    r2 = 400   # mm
    return n*n*(1-r1*(n-1)/r2/n)**2


#Cv factor from Carr and Zimm
def CvFormula(n):
    r1 = 6.26  # mm
    r2 = 15.25 # mm
    a = 4      # mm
    l = 6.26*2 # mm
    return 1 - (r1*(a+l)/(r2-r1))/(2*(n*l+r1*(a+l)/(r2-r1)))


plt.style.use("seaborn-muted")

if __name__ == "__main__":

    rindex = [1, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5]

    """ 
    # === point source == #
    filelist = []
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex10.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex105.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex11.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex115.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex12.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex125.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex13.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex135.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex14.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex145.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/point/rindex15.root")
    nbins = [50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50];
    nlow  = [5400, 4900, 4400, 4000, 3700, 3400, 3100, 2850, 2600, 2400, 2200];
    nhigh = [5800, 5300, 4800, 4400, 4100, 3800, 3500, 3250, 3000, 2800, 2600];
    #nlow  = [3000, 2750, 2450, 2250, 2050, 1850, 1700, 1600, 1450, 1350, 1200]
    #nhigh = [3400, 3100, 2850, 2550, 2350, 2200, 2050, 1900, 1750, 1650, 1500]

    nphoton_arr_point = []
    enphoton_arr_point = []
    flag = 0; ref = 1; ref_err = 1;
    for name, nb, nl, nh in zip(filelist, nbins, nlow, nhigh):
        print(name)
        #nphoton_arr.append( fitHist(name, nb, nl, nh) )
        nph, eph = fitHist( name, nb, nl, nh )
        if flag == 0:
            ref = nph
            ref_err = eph
            flag = 1
        #nphoton_arr_point.append(nph/ref)
        #enphoton_arr_point.append( np.sqrt(eph*eph/ref/ref + ref_err*ref_err*nph*nph/ref/ref/ref/ref) )
        nphoton_arr_point.append(nph)
        enphoton_arr_point.append(eph)
    
    """
    flag = 0; ref_cn = 1;
    cn_array = []
    for ri in rindex:
        tmp_cn = CnFormula(ri)
        cn_array.append(tmp_cn)
        if flag == 0:
            ref_cn = tmp_cn
            flag = 1

    """
    # === line1 source == #
    filelist = []
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex10.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex105.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex11.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex115.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex12.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex125.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex13.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex135.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex14.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex145.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line1/rindex15.root")
    nbins = [50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50];
    nlow  = [];
    nhigh = [];
    
    nphoton_arr_line1 = []
    enphoton_arr_line1 = []
    flag = 0; ref = 1; ref_err = 1;
    for name, nb, nl, nh in zip(filelist, nbins, nlow, nhigh):
        print(name)
        #nphoton_arr_line.append( fitHist(name, nb, nl, nh) )
        nph, eph = fitHist( name, nb, nl, nh )
        if flag == 0:
            ref = nph
            ref_err = eph
            flag = 1
        nphoton_arr_line1.append(nph/ref)
        enphoton_arr_line1.append( np.sqrt(eph*eph/ref/ref + ref_err*ref_err*nph*nph/ref/ref/ref/ref) )
    
    """

    
    # === line2 source == #
    filelist = []
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex10.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex105.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex11.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex115.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex12.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex125.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex13.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex135.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex14.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex145.root")
    filelist.append("/junofs/users/yumiao/simulation/Rayleigh/Simulation/jobs/line_apt1/rindex15.root")
    nbins = [50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50];
    #nlow  = [1250, 1150, 1050, 950,  850,  800,  700, 650, 600, 550, 500];
    #nhigh = [1550, 1450, 1300, 1200, 1100, 1050, 950, 900, 850, 760, 720] ;

    
    nphoton_arr_line2 = []
    enphoton_arr_line2 = []
    flag = 0; ref = 1; ref_err = 1;
    for name, nb, nl, nh in zip(filelist, nbins, nlow, nhigh):
        print(name)
        #nphoton_arr_line.append( fitHist(name, nb, nl, nh) )
        nph, eph = fitHist( name, nb, nl, nh )
        if flag == 0:
            ref = nph
            ref_err = eph
            flag = 1
        #nphoton_arr_line2.append(nph/ref)
        #enphoton_arr_line2.append( np.sqrt(eph*eph/ref/ref + ref_err*ref_err*nph*nph/ref/ref/ref/ref) )
        nphoton_arr_line2.append(nph)
        enphoton_arr_line2.append(eph)

    

    # == absolute plot == #
    origin_angle = []
    real_angle   = []
    Cv_array     = []
    for ri in rindex:
        origin_angle.append(0.2)
        real_angle.append(0.07485)
        Cv_array.append(CvFormula(ri))


    # Cv plot
    #plt.plot(rindex, 1-np.array(Cv_array))
    #plt.xlabel("refractive index")
    #plt.ylabel("Cv")
    #plt.show()


    # == subplot share xaxis == #
    #ax1 = plt.subplot(211)
    #plt.errorbar(rindex, nphoton_arr_line2, yerr=enphoton_arr_line2, fmt='o-', label='G4 sim: line2 source')
    #plt.plot(rindex, 10000*(np.array(real_angle)/np.array(origin_angle))**2/np.array(cn_array), 's-', label='Cn pred' )
    #plt.ylabel("nphoton")
    #plt.legend()
    #ax2 = plt.subplot(212, sharex=ax1)
    #plt.plot(rindex, (10000*(np.array(real_angle)/np.array(origin_angle))**2/np.array(cn_array)-np.array(nphoton_arr_line2))/np.array(nphoton_arr_line2),
    #        'v-', color='violet' )
    #plt.xlabel("refractive index")
    #plt.ylabel("relative diff")
    #plt.show()


    # == absolute plot == #
    plt.errorbar(rindex, nphoton_arr_line2, yerr=enphoton_arr_line2, fmt='o-', label='G4 sim: line2 source')
    ##plt.plot(rindex, 10000*np.array(cn_array), 's-', label='Cn pred' )
    plt.plot(rindex, 10000*(np.array(real_angle)/np.array(origin_angle))**2/np.array(cn_array), 's-', label='Cn pred' )
    plt.legend()
    plt.xlabel('refractive index')
    plt.ylabel('photon number')
    plt.title('absolute photon number')
    plt.grid(True)
    plt.show()
    #plt.savefig("line_abs.pdf")

    # == relative ratio plot == #
    #plt.errorbar(rindex, np.array(nphoton_arr_point), yerr=enphoton_arr_point, fmt="o-", label='G4 sim: point source')
    #plt.errorbar(rindex, np.array(nphoton_arr_line1), yerr=enphoton_arr_line1, fmt="o-", label='G4 sim: line source (20mm)')
    #plt.errorbar(rindex, np.array(nphoton_arr_line2), yerr=enphoton_arr_line2, fmt="o-", label='G4 sim: line source (6.26mm)')
    #plt.plot(rindex, 1./np.array(rindex)**2, "s--", label=r"$\frac{1}{n^{2}}$")
    #plt.plot(rindex, ref_cn/np.array(cn_array), "-.", color="tomato", label="Cn factor")
    #plt.legend()
    #plt.grid(True)
    #plt.xlabel("rindex")
    #plt.ylabel("nphoton ratio")
    #plt.title("relative ratio")
    #plt.show()
    #plt.savefig("line_rela.pdf")

