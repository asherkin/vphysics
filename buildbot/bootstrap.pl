#!/usr/bin/perl
# vim: set ts=2 sw=2 tw=99 noet: 

use strict;
use Cwd;
use File::Basename;
use File::Path;

my ($myself, $path) = fileparse($0);
chdir($path);

require 'helpers.pm';

#Go back above build dir
chdir(Build::PathFormat('../..'));

#Get the source path.
our ($root) = getcwd();

my $reconf = 0;

#Create output folder if it doesn't exist.
if (!(-d 'OUTPUT')) {
	$reconf = 1;
} else {
	if (-f 'OUTPUT/sentinel') {
		my @s = stat('OUTPUT/sentinel');
		my $mtime = $s[9];
		my @files = ('build/buildbot/pushbuild.txt', 'build/AMBuildScript', 'build/buildbot/product.version');
		my ($i);
		for ($i = 0; $i <= $#files; $i++) {
			if (IsNewer($files[$i], $mtime)) {
				$reconf = 1;
				last;
			}
		}
	} else {
		$reconf = 1;
	}
}

if ($reconf) {
	rmtree('OUTPUT');
	mkdir('OUTPUT') or die("Failed to create output folder: $!\n");
	chdir('OUTPUT');
	my ($result);
	print "Attempting to reconfigure...\n";
	
	#update and configure shiz
    if ($^O eq "linux") {
		my @sdks = ('sourcemod-1.3', 'mmsource-1.8', 'hl2sdk', 'hl2sdk-ob', 'hl2sdk-ob-valve', 'hl2sdk-l4d', 'hl2sdk-l4d2');
		my ($sdk);
		foreach $sdk (@sdks) {
			print 'Updating checkout of ', $sdk, ' on ' $^O, '\n';
			$result = `hg pull -u /home/builds/common/$sdk`;
			print $result;
		}
		
		$ENV{'SOURCEMOD13'} = '/home/builds/common/sourcemod-1.3';
		$ENV{'MMSOURCE18'} = '/home/builds/common/mmsource-1.8';
		
		$ENV{'HL2SDK'} = '/home/builds/common/hl2sdk';
		$ENV{'HL2SDKOB'} = '/home/builds/common/hl2sdk-ob';
		$ENV{'HL2SDKOBVALVE'} = '/home/builds/common/hl2sdk-ob-valve';
		$ENV{'HL2SDKL4D'} = '/home/builds/common/hl2sdk-l4d';
		$ENV{'HL2SDKL4D2'} = '/home/builds/common/hl2sdk-l4d2';
	} elsif ($^O eq "darwin") {
		my @sdks = ('sourcemod-1.3', 'mmsource-1.8', 'hl2sdk-ob-valve');
		my ($sdk);
		foreach $sdk (@sdks) {
			print 'Updating checkout of ', $sdk, ' on ' $^O, '\n';
			$result = `hg pull -u /Users/builds/builds/common/$sdk`;
			print $result;
		}
		
		$ENV{'SOURCEMOD13'} = '/Users/builds/builds/common/sourcemod-1.3';
		$ENV{'MMSOURCE18'} = '/Users/builds/builds/common/mmsource-1.8';
		
		$ENV{'HL2SDKOBVALVE'} = '/Users/builds/builds/common/hl2sdk-ob-valve';
	} else {
		my @sdks = ('sourcemod-1.3', 'mmsource-1.8', 'hl2sdk', 'hl2sdk-darkm', 'hl2sdk-ob', 'hl2sdk-ob-valve', 'hl2sdk-l4d', 'hl2sdk-l4d2', 'hl2sdk-swarm');
		my ($sdk);
		foreach $sdk (@sdks) {
			print 'Updating checkout of ', $sdk, ' on ' $^O, '\n';
			$result = `hg pull -u C:/Scripts/common/$sdk`;
			print $result;
		}
		
		$ENV{'SOURCEMOD13'} = 'C:/Scripts/common/sourcemod-1.3';
		$ENV{'MMSOURCE18'} = 'C:/Scripts/common/mmsource-1.8';
		
		$ENV{'HL2SDK'} = 'C:/Scripts/common/hl2sdk';
		$ENV{'HL2SDK-DARKM'} = 'C:/Scripts/common/hl2sdk-darkm';
		$ENV{'HL2SDKOB'} = 'C:/Scripts/common/hl2sdk-ob';
		$ENV{'HL2SDKOBVALVE'} = 'C:/Scripts/common/hl2sdk-ob-valve';
		$ENV{'HL2SDKL4D'} = 'C:/Scripts/common/hl2sdk-l4d';
		$ENV{'HL2SDKL4D2'} = 'C:/Scripts/common/hl2sdk-l4d2';
		$ENV{'HL2SDK-SWARM'} = 'C:/Scripts/common/hl2sdk-swarm';
	}
	
	#my debugging shiz
	print "CWD: ", getcwd(), "\n";
	print "MMSOURCE18: ", $ENV{'MMSOURCE18'}, "\n";
	print "HL2SDKOBVALVE: ", $ENV{'HL2SDKOBVALVE'}, "\n";
	print "SOURCEMOD13: ", $ENV{'SOURCEMOD13'}, "\n";
	
	#configure AMBuild
	if ($^O eq "linux") {
		$result = `CC=gcc-4.1 CXX=gcc-4.1 python3.1 ../build/configure.py --enable-optimize`;
	} elsif ($^O eq "darwin") {
		$result = `CC=gcc-4.2 CXX=gcc-4.2 python3.1 ../build/configure.py --enable-optimize`;
	} else {
		$result = `C:\\Python31\\Python.exe ..\\build\\configure.py --enable-optimize`;
	}
	print "$result\n";
	if ($? != 0) {
		die('Could not configure!');
	}
	open(FILE, '>sentinel');
	print FILE "this is nothing.\n";
	close(FILE);
}

sub IsNewer
{
	my ($file, $time) = (@_);

	my @s = stat($file);
	my $mtime = $s[9];
	return $mtime > $time;
}

exit(0);


