void BrVsRun_gm2pro_daq_offline_dqc_run3N_5207A_34184_34618()
{
//=========Macro generated from canvas: c/c
//=========  (Sun Jan 30 09:48:52 2022) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->SetHighLightColor(2);
   c->Range(34075.5,-4,34726.5,6);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1003[212] = {
   34184,
   34185,
   34186,
   34187,
   34188,
   34189,
   34190,
   34191,
   34192,
   34193,
   34203,
   34204,
   34205,
   34206,
   34207,
   34208,
   34209,
   34210,
   34212,
   34213,
   34214,
   34215,
   34216,
   34217,
   34218,
   34219,
   34220,
   34221,
   34222,
   34223,
   34224,
   34226,
   34227,
   34274,
   34278,
   34279,
   34281,
   34282,
   34283,
   34284,
   34285,
   34287,
   34288,
   34289,
   34290,
   34291,
   34292,
   34293,
   34294,
   34295,
   34296,
   34297,
   34298,
   34299,
   34300,
   34301,
   34302,
   34305,
   34306,
   34308,
   34309,
   34310,
   34311,
   34312,
   34313,
   34314,
   34315,
   34316,
   34317,
   34318,
   34319,
   34320,
   34321,
   34322,
   34323,
   34324,
   34325,
   34330,
   34334,
   34335,
   34337,
   34338,
   34339,
   34340,
   34341,
   34342,
   34343,
   34344,
   34345,
   34346,
   34347,
   34348,
   34349,
   34350,
   34351,
   34352,
   34353,
   34354,
   34355,
   34357,
   34358,
   34359,
   34360,
   34361,
   34362,
   34396,
   34397,
   34399,
   34400,
   34402,
   34403,
   34404,
   34405,
   34406,
   34409,
   34411,
   34412,
   34413,
   34414,
   34415,
   34416,
   34417,
   34418,
   34419,
   34420,
   34421,
   34422,
   34423,
   34424,
   34428,
   34429,
   34430,
   34433,
   34434,
   34435,
   34436,
   34437,
   34438,
   34439,
   34440,
   34441,
   34442,
   34443,
   34444,
   34470,
   34473,
   34474,
   34475,
   34476,
   34477,
   34479,
   34480,
   34481,
   34482,
   34483,
   34485,
   34486,
   34490,
   34491,
   34494,
   34495,
   34497,
   34498,
   34499,
   34506,
   34512,
   34518,
   34521,
   34522,
   34523,
   34524,
   34525,
   34526,
   34527,
   34528,
   34529,
   34530,
   34531,
   34532,
   34533,
   34535,
   34536,
   34581,
   34582,
   34583,
   34584,
   34585,
   34586,
   34587,
   34588,
   34589,
   34590,
   34591,
   34594,
   34595,
   34598,
   34599,
   34600,
   34601,
   34602,
   34604,
   34605,
   34606,
   34607,
   34610,
   34611,
   34612,
   34613,
   34614,
   34615,
   34616,
   34618};
   Double_t Graph0_fy1003[212] = {
   9.663853,
   9.850627,
   9.60894,
   9.515813,
   9.479072,
   11.06586,
   9.595216,
   9.540803,
   10.18121,
   9.621117,
   10.04511,
   9.970953,
   9.985068,
   10.03331,
   9.835518,
   9.546355,
   9.966969,
   9.871241,
   9.811723,
   9.971927,
   10.18663,
   9.776114,
   9.920275,
   9.696211,
   9.196682,
   9.709588,
   9.47204,
   9.556285,
   9.467447,
   9.574329,
   9.474106,
   9.309346,
   8.866661,
   13.75621,
   9.804976,
   9.74107,
   9.91766,
   9.703245,
   9.673036,
   9.717402,
   9.652287,
   9.586539,
   10.29821,
   10.46418,
   9.646181,
   9.609313,
   9.508579,
   10.26248,
   9.413884,
   9.386518,
   9.459641,
   9.551341,
   9.596108,
   9.414328,
   9.509967,
   9.479134,
   9.414368,
   9.264248,
   9.341513,
   9.140342,
   9.294015,
   9.207316,
   9.129401,
   9.102062,
   9.37114,
   9.276117,
   9.025822,
   9.159595,
   9.414597,
   9.541804,
   9.280142,
   9.39999,
   9.556249,
   9.225939,
   9.518064,
   10.13,
   9.507744,
   10.35303,
   10.18251,
   10.18338,
   10.23176,
   10.24186,
   10.36325,
   13.06507,
   10.1365,
   10.11944,
   10.28891,
   10.38139,
   10.48068,
   8.721623,
   10.23628,
   10.23138,
   10.33663,
   9.158061,
   8.927335,
   9.400633,
   9.930511,
   9.962296,
   10.10411,
   10.23526,
   10.04029,
   10.21494,
   10.15466,
   9.433415,
   9.9846,
   10.02608,
   10.07225,
   10.04366,
   10.12144,
   10.19831,
   10.22929,
   10.15685,
   9.784382,
   9.513317,
   10.23755,
   10.27116,
   10.17398,
   10.14213,
   10.24451,
   10.40875,
   10.2872,
   9.448471,
   10.33565,
   10.41498,
   10.6489,
   10.56671,
   10.58793,
   10.64308,
   10.77811,
   10.46357,
   10.33377,
   10.29303,
   10.36938,
   10.57607,
   10.25504,
   10.52781,
   10.602,
   10.40409,
   10.47601,
   10.55893,
   10.05054,
   10.48972,
   10.42224,
   10.41145,
   10.09158,
   10.1594,
   10.10036,
   9.244233,
   10.25551,
   10.12133,
   6.927918,
   9.934772,
   10.2524,
   10.34725,
   10.13565,
   10.36251,
   10.30703,
   10.32785,
   10.24012,
   10.33637,
   9.288276,
   10.19204,
   10.02423,
   9.891202,
   10.33824,
   10.85734,
   9.487164,
   11.00758,
   10.16299,
   10.04333,
   10.11396,
   9.989686,
   10.15168,
   10.08849,
   9.837519,
   10.07896,
   10.01036,
   9.90641,
   9.964777,
   9.974797,
   9.982714,
   9.881844,
   10.61445,
   10.00252,
   10.0107,
   9.846969,
   9.902818,
   9.860666,
   9.986191,
   9.812683,
   10.16101,
   9.933516,
   10.67527,
   9.979758,
   9.95964,
   9.441167,
   9.904964,
   9.984047,
   9.85956,
   10.17704,
   9.964709,
   9.926438,
   9.648042,
   9.706763,
   9.663024,
   9.724117,
   9.815836,
   9.67379,
   9.769567,
   9.661477,
   9.77673,
   9.669671};
   Double_t Graph0_fex1003[212] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1003[212] = {
   4.360615,
   4.364107,
   4.359519,
   4.35773,
   4.357563,
   4.425966,
   4.371203,
   4.35822,
   4.626083,
   4.360977,
   4.367575,
   4.366237,
   4.366503,
   4.368464,
   4.364605,
   4.368555,
   4.36618,
   4.364446,
   4.36426,
   4.367799,
   4.371569,
   4.362718,
   4.398129,
   4.3635,
   4.358673,
   4.362406,
   4.35735,
   4.358537,
   4.356759,
   4.358857,
   4.356966,
   4.396272,
   4.371944,
   4.636548,
   4.369504,
   4.363487,
   4.369748,
   4.361491,
   4.360835,
   4.362468,
   4.363984,
   4.359141,
   4.445773,
   4.44914,
   4.360553,
   4.359965,
   4.357585,
   4.509843,
   4.359121,
   4.361984,
   4.357282,
   4.358768,
   4.370863,
   4.356081,
   4.359663,
   4.358505,
   4.359233,
   4.352748,
   4.359829,
   4.350059,
   4.353266,
   4.351504,
   4.349832,
   4.349247,
   4.365231,
   4.35312,
   4.348467,
   4.350478,
   4.355699,
   4.358214,
   4.353581,
   4.355408,
   4.3585,
   4.351919,
   4.358814,
   4.37083,
   4.607747,
   4.376695,
   4.370089,
   4.369997,
   4.370773,
   4.370963,
   4.3735,
   4.696469,
   4.371378,
   4.368949,
   4.371751,
   4.375219,
   4.383116,
   4.577293,
   4.370925,
   4.370752,
   4.375225,
   4.351611,
   4.34555,
   4.355425,
   4.369094,
   4.366057,
   4.368695,
   4.370833,
   4.367445,
   4.372395,
   4.369442,
   4.372747,
   4.367995,
   4.367193,
   4.368017,
   4.367922,
   4.36978,
   4.37034,
   4.371527,
   4.369501,
   4.362853,
   4.357643,
   4.392353,
   4.371492,
   4.369823,
   4.369262,
   4.371031,
   4.373764,
   4.371723,
   4.363072,
   4.372614,
   4.374032,
   4.377625,
   4.376318,
   4.376692,
   4.377775,
   4.383534,
   4.375915,
   4.373335,
   4.376271,
   4.373111,
   4.377512,
   4.371323,
   4.375708,
   4.376894,
   4.373667,
   4.374849,
   4.376961,
   4.423316,
   4.375101,
   4.373968,
   4.373802,
   4.368346,
   4.370055,
   4.368501,
   4.360995,
   4.385275,
   4.369191,
   4.435495,
   4.375827,
   4.371121,
   4.3735,
   4.369625,
   4.37303,
   4.372039,
   4.372393,
   4.37091,
   4.375776,
   4.410111,
   4.370308,
   4.367443,
   4.369696,
   4.375732,
   4.382463,
   4.610218,
   4.466826,
   4.369887,
   4.367576,
   4.369708,
   4.366547,
   4.374829,
   4.368385,
   4.363823,
   4.368232,
   4.366952,
   4.366029,
   4.3661,
   4.367,
   4.366421,
   4.364764,
   4.432326,
   4.366766,
   4.372513,
   4.36398,
   4.365007,
   4.364215,
   4.366473,
   4.363331,
   4.369559,
   4.365639,
   4.42523,
   4.366373,
   4.366,
   4.372098,
   4.365026,
   4.366444,
   4.364213,
   4.370555,
   4.366114,
   4.368187,
   4.360229,
   4.361674,
   4.360587,
   4.36167,
   4.363376,
   4.360865,
   4.36901,
   4.360506,
   4.362654,
   4.360673};
   TGraphErrors *gre = new TGraphErrors(212,Graph0_fx1003,Graph0_fy1003,Graph0_fex1003,Graph0_fey1003);
   gre->SetName("Graph0");
   gre->SetTitle(";Run number;#LTB_{r}#GT [ppm]");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   gre->SetFillColor(ci);
   gre->SetFillStyle(3004);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1003 = new TH1F("Graph_Graph1003","",212,34140.6,34661.4);
   Graph_Graph1003->SetMinimum(-3);
   Graph_Graph1003->SetMaximum(5);
   Graph_Graph1003->SetDirectory(0);
   Graph_Graph1003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1003->SetLineColor(ci);
   Graph_Graph1003->GetXaxis()->SetTitle("Run number");
   Graph_Graph1003->GetXaxis()->CenterTitle(true);
   Graph_Graph1003->GetXaxis()->SetLabelFont(42);
   Graph_Graph1003->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1003->GetXaxis()->SetTitleOffset(1.1);
   Graph_Graph1003->GetXaxis()->SetTitleFont(42);
   Graph_Graph1003->GetYaxis()->SetTitle("#LTB_{r}#GT [ppm]");
   Graph_Graph1003->GetYaxis()->CenterTitle(true);
   Graph_Graph1003->GetYaxis()->SetNdivisions(4000510);
   Graph_Graph1003->GetYaxis()->SetLabelFont(42);
   Graph_Graph1003->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1003->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1003->GetYaxis()->SetTitleFont(42);
   Graph_Graph1003->GetZaxis()->SetLabelFont(42);
   Graph_Graph1003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1003);
   
   gre->Draw("a3");
   
   Double_t Graph1_fx1004[212] = {
   34184,
   34185,
   34186,
   34187,
   34188,
   34189,
   34190,
   34191,
   34192,
   34193,
   34203,
   34204,
   34205,
   34206,
   34207,
   34208,
   34209,
   34210,
   34212,
   34213,
   34214,
   34215,
   34216,
   34217,
   34218,
   34219,
   34220,
   34221,
   34222,
   34223,
   34224,
   34226,
   34227,
   34274,
   34278,
   34279,
   34281,
   34282,
   34283,
   34284,
   34285,
   34287,
   34288,
   34289,
   34290,
   34291,
   34292,
   34293,
   34294,
   34295,
   34296,
   34297,
   34298,
   34299,
   34300,
   34301,
   34302,
   34305,
   34306,
   34308,
   34309,
   34310,
   34311,
   34312,
   34313,
   34314,
   34315,
   34316,
   34317,
   34318,
   34319,
   34320,
   34321,
   34322,
   34323,
   34324,
   34325,
   34330,
   34334,
   34335,
   34337,
   34338,
   34339,
   34340,
   34341,
   34342,
   34343,
   34344,
   34345,
   34346,
   34347,
   34348,
   34349,
   34350,
   34351,
   34352,
   34353,
   34354,
   34355,
   34357,
   34358,
   34359,
   34360,
   34361,
   34362,
   34396,
   34397,
   34399,
   34400,
   34402,
   34403,
   34404,
   34405,
   34406,
   34409,
   34411,
   34412,
   34413,
   34414,
   34415,
   34416,
   34417,
   34418,
   34419,
   34420,
   34421,
   34422,
   34423,
   34424,
   34428,
   34429,
   34430,
   34433,
   34434,
   34435,
   34436,
   34437,
   34438,
   34439,
   34440,
   34441,
   34442,
   34443,
   34444,
   34470,
   34473,
   34474,
   34475,
   34476,
   34477,
   34479,
   34480,
   34481,
   34482,
   34483,
   34485,
   34486,
   34490,
   34491,
   34494,
   34495,
   34497,
   34498,
   34499,
   34506,
   34512,
   34518,
   34521,
   34522,
   34523,
   34524,
   34525,
   34526,
   34527,
   34528,
   34529,
   34530,
   34531,
   34532,
   34533,
   34535,
   34536,
   34581,
   34582,
   34583,
   34584,
   34585,
   34586,
   34587,
   34588,
   34589,
   34590,
   34591,
   34594,
   34595,
   34598,
   34599,
   34600,
   34601,
   34602,
   34604,
   34605,
   34606,
   34607,
   34610,
   34611,
   34612,
   34613,
   34614,
   34615,
   34616,
   34618};
   Double_t Graph1_fy1004[212] = {
   9.663853,
   9.850627,
   9.60894,
   9.515813,
   9.479072,
   11.06586,
   9.595216,
   9.540803,
   10.18121,
   9.621117,
   10.04511,
   9.970953,
   9.985068,
   10.03331,
   9.835518,
   9.546355,
   9.966969,
   9.871241,
   9.811723,
   9.971927,
   10.18663,
   9.776114,
   9.920275,
   9.696211,
   9.196682,
   9.709588,
   9.47204,
   9.556285,
   9.467447,
   9.574329,
   9.474106,
   9.309346,
   8.866661,
   13.75621,
   9.804976,
   9.74107,
   9.91766,
   9.703245,
   9.673036,
   9.717402,
   9.652287,
   9.586539,
   10.29821,
   10.46418,
   9.646181,
   9.609313,
   9.508579,
   10.26248,
   9.413884,
   9.386518,
   9.459641,
   9.551341,
   9.596108,
   9.414328,
   9.509967,
   9.479134,
   9.414368,
   9.264248,
   9.341513,
   9.140342,
   9.294015,
   9.207316,
   9.129401,
   9.102062,
   9.37114,
   9.276117,
   9.025822,
   9.159595,
   9.414597,
   9.541804,
   9.280142,
   9.39999,
   9.556249,
   9.225939,
   9.518064,
   10.13,
   9.507744,
   10.35303,
   10.18251,
   10.18338,
   10.23176,
   10.24186,
   10.36325,
   13.06507,
   10.1365,
   10.11944,
   10.28891,
   10.38139,
   10.48068,
   8.721623,
   10.23628,
   10.23138,
   10.33663,
   9.158061,
   8.927335,
   9.400633,
   9.930511,
   9.962296,
   10.10411,
   10.23526,
   10.04029,
   10.21494,
   10.15466,
   9.433415,
   9.9846,
   10.02608,
   10.07225,
   10.04366,
   10.12144,
   10.19831,
   10.22929,
   10.15685,
   9.784382,
   9.513317,
   10.23755,
   10.27116,
   10.17398,
   10.14213,
   10.24451,
   10.40875,
   10.2872,
   9.448471,
   10.33565,
   10.41498,
   10.6489,
   10.56671,
   10.58793,
   10.64308,
   10.77811,
   10.46357,
   10.33377,
   10.29303,
   10.36938,
   10.57607,
   10.25504,
   10.52781,
   10.602,
   10.40409,
   10.47601,
   10.55893,
   10.05054,
   10.48972,
   10.42224,
   10.41145,
   10.09158,
   10.1594,
   10.10036,
   9.244233,
   10.25551,
   10.12133,
   6.927918,
   9.934772,
   10.2524,
   10.34725,
   10.13565,
   10.36251,
   10.30703,
   10.32785,
   10.24012,
   10.33637,
   9.288276,
   10.19204,
   10.02423,
   9.891202,
   10.33824,
   10.85734,
   9.487164,
   11.00758,
   10.16299,
   10.04333,
   10.11396,
   9.989686,
   10.15168,
   10.08849,
   9.837519,
   10.07896,
   10.01036,
   9.90641,
   9.964777,
   9.974797,
   9.982714,
   9.881844,
   10.61445,
   10.00252,
   10.0107,
   9.846969,
   9.902818,
   9.860666,
   9.986191,
   9.812683,
   10.16101,
   9.933516,
   10.67527,
   9.979758,
   9.95964,
   9.441167,
   9.904964,
   9.984047,
   9.85956,
   10.17704,
   9.964709,
   9.926438,
   9.648042,
   9.706763,
   9.663024,
   9.724117,
   9.815836,
   9.67379,
   9.769567,
   9.661477,
   9.77673,
   9.669671};
   Double_t Graph1_fex1004[212] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1004[212] = {
   0.07945067,
   0.07938023,
   0.07674639,
   0.07808205,
   0.1067397,
   0.636346,
   0.3462023,
   0.07811891,
   1.584487,
   0.1324697,
   0.07708598,
   0.07604647,
   0.07685107,
   0.1280013,
   0.1169706,
   0.3219374,
   0.0769532,
   0.07701954,
   0.1207306,
   0.1430671,
   0.1429253,
   0.07872707,
   0.5647675,
   0.167128,
   0.2772753,
   0.1229113,
   0.1034282,
   0.0790631,
   0.07701949,
   0.0771531,
   0.08152189,
   0.6443047,
   0.5225504,
   1.459383,
   0.2563306,
   0.1405448,
   0.2198552,
   0.08681502,
   0.08208932,
   0.1195616,
   0.2012585,
   0.08006151,
   0.8443413,
   0.847548,
   0.09452454,
   0.1003621,
   0.07790016,
   1.158514,
   0.1965352,
   0.2668387,
   0.1113008,
   0.09679867,
   0.3412348,
   0.09774103,
   0.1600358,
   0.142723,
   0.1990057,
   0.08288998,
   0.2435988,
   0.07709874,
   0.07724754,
   0.07932645,
   0.07741683,
   0.07725986,
   0.3243437,
   0.0899495,
   0.1191683,
   0.07787145,
   0.07652885,
   0.07656433,
   0.1081278,
   0.07664056,
   0.07680996,
   0.08086984,
   0.1264884,
   0.150741,
   1.567892,
   0.2056895,
   0.08385134,
   0.07756633,
   0.07421063,
   0.07531289,
   0.1016849,
   1.673228,
   0.1638926,
   0.08120306,
   0.07471294,
   0.1542512,
   0.2885998,
   1.526488,
   0.07885341,
   0.07330059,
   0.1759265,
   0.1310869,
   0.08349522,
   0.07693929,
   0.1997292,
   0.07448189,
   0.08199918,
   0.07422084,
   0.07430381,
   0.1538054,
   0.07389477,
   0.4062949,
   0.1420376,
   0.07431536,
   0.07475876,
   0.09738052,
   0.119009,
   0.0826622,
   0.1143441,
   0.07525504,
   0.07757368,
   0.07571112,
   0.4583011,
   0.07729636,
   0.07685312,
   0.07625012,
   0.07677098,
   0.07539288,
   0.0747142,
   0.2640853,
   0.07942188,
   0.08514549,
   0.07400618,
   0.07418244,
   0.07635191,
   0.08820543,
   0.2058032,
   0.132438,
   0.1159748,
   0.218764,
   0.07534026,
   0.1241172,
   0.08342734,
   0.07526676,
   0.07491782,
   0.07410573,
   0.07413234,
   0.1130739,
   0.7336545,
   0.07591759,
   0.07417566,
   0.07497146,
   0.07410464,
   0.1024815,
   0.07417989,
   0.2993129,
   0.3736396,
   0.09261427,
   1.203378,
   0.3213991,
   0.07399528,
   0.1134794,
   0.1016813,
   0.07745628,
   0.07358447,
   0.07380723,
   0.07382282,
   0.1903241,
   0.7435448,
   0.08696251,
   0.09058903,
   0.22897,
   0.1884444,
   0.1437595,
   1.577186,
   0.897665,
   0.09119598,
   0.07905136,
   0.1212971,
   0.07444679,
   0.2391018,
   0.07984874,
   0.07673546,
   0.08069607,
   0.07673441,
   0.1220102,
   0.07441988,
   0.1112619,
   0.07434975,
   0.08430486,
   0.729903,
   0.07380604,
   0.2423302,
   0.07571852,
   0.07609008,
   0.07464555,
   0.07367513,
   0.0746264,
   0.07435867,
   0.0806948,
   0.6747862,
   0.07465122,
   0.07392442,
   0.3967072,
   0.07483978,
   0.0743139,
   0.07581815,
   0.1111837,
   0.07536421,
   0.1787807,
   0.07420772,
   0.09298659,
   0.07868591,
   0.07409465,
   0.07376128,
   0.08299314,
   0.2593975,
   0.0755363,
   0.07404285,
   0.07622041};
   gre = new TGraphErrors(212,Graph1_fx1004,Graph1_fy1004,Graph1_fex1004,Graph1_fey1004);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#0000ff");
   gre->SetFillColor(ci);
   gre->SetFillStyle(3004);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1004 = new TH1F("Graph_Graph1004","Graph",212,34140.6,34661.4);
   Graph_Graph1004->SetMinimum(4.775434);
   Graph_Graph1004->SetMaximum(16.1647);
   Graph_Graph1004->SetDirectory(0);
   Graph_Graph1004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1004->SetLineColor(ci);
   Graph_Graph1004->GetXaxis()->SetLabelFont(42);
   Graph_Graph1004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1004->GetXaxis()->SetTitleFont(42);
   Graph_Graph1004->GetYaxis()->SetLabelFont(42);
   Graph_Graph1004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1004->GetYaxis()->SetTitleOffset(0);
   Graph_Graph1004->GetYaxis()->SetTitleFont(42);
   Graph_Graph1004->GetZaxis()->SetLabelFont(42);
   Graph_Graph1004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1004);
   
   gre->Draw("p3 ");
   
   TLegend *leg = new TLegend(0.15,0.79,0.65,0.89,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph1","Uncorrelated errors","lpf");

   ci = TColor::GetColor("#0000ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3004);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph0","Correlated errors","lpf");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3004);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
