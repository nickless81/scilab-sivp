ilib_name="libsivp";

table = ["viptest", "viptest";];

// generate the gateway file
ilib_gen_gateway(ilib_name,table)

// generate a loader file
// rhs = 2;
// ilib_gen_loader(ilib_name,table);
